#ifndef PLANT_INFORMATION
#define PLANT_INFORMATION

class PlantInformation {
  public:
    int temperatureValue;
    int soilMoistureValue;
    bool isPumpRunning;
    unsigned long lastPumpActivationEpoch;
  
    String toJson();
    PlantInformation() {
      this->temperatureValue = 0;
      this->soilMoistureValue = 0;
      this->isPumpRunning = false;
      this->lastPumpActivationEpoch = 0;
    }
};

String PlantInformation::toJson() {
  String json = "{";
  json += "\"moisture\":";
  json += soilMoistureValue;
  json += ",\"temperature\":";
  json += temperatureValue;
  json += ",\"isPumpOn\":";
  json += isPumpRunning ? "true" : "false";
  json += ",\"lastPumpActivation\":";
  json += lastPumpActivationEpoch;
  json += "}";

  return json;
}

#endif
