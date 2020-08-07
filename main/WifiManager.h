#ifndef WIFI_MANAGER
#define WIFI_MANAGER

#include "Wifi.h"

class WifiManager {
  private:
    const char* WIFI_SSID = "895-7";
    const char* WIFI_PASSWORD = "4385808285";
  public:
    bool connectToWifi();
    bool isConnected();
};

bool WifiManager::isConnected() {
  if(WiFi.status() == WL_CONNECTED) {
    return true;
  }

  return false;
}

bool WifiManager::connectToWifi() {
  if(WiFi.status() != WL_CONNECTED) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 

    int connectionTry = 0;
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) { //Check for the connection
      delay(200);
      Serial.print(".");

      if(connectionTry > 5) {
        Serial.println("");
        return false;
      }

      connectionTry++;
    }
  
    Serial.println("Connected to the WiFi network");
    
  } else {
    Serial.println("Already connected to the WiFi network");
  }

  return true;
}

#endif
