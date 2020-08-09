#include "SensorManager.h"
#include "PlantInformation.h"
#include "WateringCycle.h"
#include "Relay.h"
#include "TimeManager.h"
#include "WifiManager.h"
#include "ServerManager.h"

TimeManager timeManager;
SensorManager sensorManager;
PlantInformation* plantInformation;
Relay relay(2);
WateringCycle wateringCycle;
WifiManager wifiManager;
ServerManager serverManager;

void setup(){
  Serial.begin(115200);

  plantInformation = new PlantInformation();
}

void loop() {
  Serial.println("BEGIN LOOP\n");

  wifiManager.connectToWifi();

  if(wifiManager.isConnected()) {
    timeManager.initialize();
  }
  timeManager.update();

  sensorManager.readSensors();
  plantInformation->soilMoistureValue = sensorManager.getSoilMoisture();
  plantInformation->temperatureValue = sensorManager.getTemperature();

  if(plantInformation->soilMoistureValue < 0) {
    wateringCycle.start();
  }

  if(wifiManager.isConnected()) {
    if(serverManager.gotStartRequest()) {
      wateringCycle.start();
    }
  
    if(serverManager.gotStopRequest()) {
      wateringCycle.stop();
    }
  }

  wateringCycle.update();

  if(wateringCycle.isRunning) {
    plantInformation->isPumpRunning = true;
    plantInformation->lastPumpActivationEpoch = timeManager.getCurrentEpoch();
    
    relay.close();
  } else {
    plantInformation->isPumpRunning = false;
    
    relay.open();
  }

  if(wifiManager.isConnected()) {
    serverManager.sendData(plantInformation->toJson());
  }

  Serial.println("END LOOP\n");
  delay(10 * 1000);
}
