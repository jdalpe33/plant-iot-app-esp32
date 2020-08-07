#ifndef TEMPERATURE_SENSOR
#define TEMPERATURE_SENSOR

#include "Sensor.h"
#include "OneWire.h"
#include "DallasTemperature.h"

class TemperatureSensor : public Sensor {
  private:
    OneWire oneWire;
    DallasTemperature sensors;
  public:
    TemperatureSensor(int sensorPin) {
      oneWire = OneWire(sensorPin);
      sensors = DallasTemperature(&oneWire);    
      
      sensors.begin();
    }
    void readValue();
};

void TemperatureSensor::readValue() {
  sensors.requestTemperatures();
  value = sensors.getTempCByIndex(0);
}

#endif
