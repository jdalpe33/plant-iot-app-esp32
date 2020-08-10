#ifndef SOIL_MOISTURE_SENSOR
#define SOIL_MOISTURE_SENSOR

#include "Sensor.h"

class SoilMoistureSensor : public Sensor {
  private:
    int sensorPin;
    const int AIR_BASE_VALUE = 3250;
    const int WATER_BASE_VALUE = 1380;
  public:
    SoilMoistureSensor(int sensorPin) { this->sensorPin = sensorPin; }
    void readValue();
};

void SoilMoistureSensor::readValue() {
  int soilMoistureValue = analogRead(sensorPin);
  Serial.println(soilMoistureValue);
  value = 0;
  if(soilMoistureValue <= AIR_BASE_VALUE && soilMoistureValue >= WATER_BASE_VALUE) {
    value = map(soilMoistureValue, AIR_BASE_VALUE, WATER_BASE_VALUE, 0, 100);
  } else if (soilMoistureValue < WATER_BASE_VALUE) {
    value = 100;
  }
}

#endif
