#ifndef SENSOR_MANAGER
#define SENSOR_MANAGER

#include "Sensor.h"
#include "SoilMoistureSensor.h"
#include "TemperatureSensor.h"

class SensorManager {
  public:
    int getSoilMoisture();
    int getTemperature();
    void readSensors();
  private:
    Sensor* soilMoistureSensor = new SoilMoistureSensor (15);
    Sensor* temperatureSensor = new TemperatureSensor (0);
};

void SensorManager::readSensors() {
  soilMoistureSensor->readValue();
  temperatureSensor->readValue();
}

int SensorManager::getSoilMoisture() {
  Serial.print("SENSOR_MANAGER -> GET SOIL MOISTURE : ");
  Serial.println(soilMoistureSensor->getValue());
  return soilMoistureSensor->getValue();
}

int SensorManager::getTemperature() {
  Serial.print("SENSOR_MANAGER -> GET TEMPERATURE : ");
  Serial.println(temperatureSensor->getValue());
  return temperatureSensor->getValue();
}

#endif
