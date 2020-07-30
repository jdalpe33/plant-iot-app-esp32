#include "WiFi.h"
#include "HTTPClient.h"
#include "NTPClient.h"
#include "WiFiUdp.h"

const char* WIFI_SSID = "richnugs";
const char* WIFI_PASSWORD = "anto9090909";
const String DATA_URL = "http://www.plant-iot-app.com/addlog";

const int AIR_BASE_VALUE = 0;
const int WATER_BASE_VALUE = 0;

const int PUMP_RELAY_PIN = 0;
const int SOIL_MOISTURE_SENSOR_PIN = A0;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

int soilMoisturePercent = -1;
bool isPumpRunning = false;
unsigned long lastPumpActivationEpoch = 0;
unsigned long  currentEpoch = 0;

void setup(){
  Serial.begin(115200);
  pinMode(PUMP_RELAY_PIN, OUTPUT);
}

void loop() {
  Serial.println("BEGIN LOOP\n");
  soilMoisturePercent = getSoilMoisturePercent();

  if(soilMoisturePercent < 50 && soilMoisturePercent >= 0) {
    startPump();
  } else {
    stopPump();
  }

  sendDataToServer();

  Serial.println("END LOOP, WAITING FOR 60 SEC\n");
  delay(60 * 1000); // WAIT FOR 1 MINUTE
}

bool connectToWifi() {
  if(WiFi.status() != WL_CONNECTED) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 

    int connectionTry = 0;
    while (WiFi.status() != WL_CONNECTED) { //Check for the connection
      delay(1000);
      Serial.println("Connecting to WiFi..");

      if(connectionTry > 5) {
        return false;
      }

      connectionTry++;
    }
  
    Serial.println("Connected to the WiFi network");
    
  } else {
    Serial.println("Already connected to the WiFi network");
  }

  timeClient.begin();
  timeClient.setTimeOffset(3600 * -4);

  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  lastPumpActivationEpoch = timeClient.getEpochTime();
  Serial.println(lastPumpActivationEpoch);
  
  if(isPumpRunning) {
    lastPumpActivationEpoch = currentEpoch;
  }

  return true;
}

String buildJsonData() {
  String json = "{";
  json += "\"moisture\":";
  json += soilMoisturePercent;
  json += ",\"isPumpOn\":";
  json += isPumpRunning ? "true" : "false";
  json += ",\"lastPumpActivation\":";
  json += lastPumpActivationEpoch;
  json += "}";

  Serial.print("Built json :");
  Serial.println(json);

  return json;
}

void sendDataToServer() {

  bool isConnectedToWifi = connectToWifi();
  
  if(isConnectedToWifi) {
    HTTPClient http;
 
    http.begin(DATA_URL);//"http://localhost:3000/addlog"); //Specify destination for HTTP request
    http.addHeader("Content-Type", "application/json"); //Specify content-type header

    int httpResponseCode = http.POST(buildJsonData()); //Send the actual POST request

    if(httpResponseCode>0){
    String response = http.getString();  //Get the response to the request
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
    }else{
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }
  }
}

int getSoilMoisturePercent() {
  int soilMoistureValue = analogRead(SOIL_MOISTURE_SENSOR_PIN);

  Serial.print("SOIL MOISTURE VALUE:");
  Serial.println(soilMoistureValue);

  int soilMoisturePercent = map(soilMoistureValue, AIR_BASE_VALUE, WATER_BASE_VALUE, 0, 100);

  Serial.print("SOIL MOISTURE PERCENT:");
  Serial.println(soilMoisturePercent);

  return soilMoisturePercent;
}

void startPump() {
  Serial.println("START PUMP");
  lastPumpActivationEpoch = currentEpoch;
  isPumpRunning = true;
  digitalWrite(PUMP_RELAY_PIN, HIGH);
}

void stopPump() {
  Serial.println("STOP PUMP");
  isPumpRunning = false;
  digitalWrite(PUMP_RELAY_PIN, LOW);
}
