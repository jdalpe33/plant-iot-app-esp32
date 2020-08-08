#ifndef SERVER_MANAGER
#define SERVER_MANAGER

#include "HTTPClient.h"
#include "Variables.h"

class ServerManager {
  private:
  public:
    boolean gotStartRequest();
    boolean gotStopRequest();
    boolean sendData(String data);
};

boolean ServerManager::gotStartRequest() {
  HTTPClient http;
  http.begin(START_URL);

  int httpResponseCode = http.GET();

  if(httpResponseCode>0){
    String response = http.getString();  //Get the response to the request
  
    if (httpResponseCode == 200) {
      return true;
    } else {
      return false;
    }
  }
}
boolean ServerManager::gotStopRequest() {
  HTTPClient http;
  http.begin(STOP_URL);

  int httpResponseCode = http.GET();

  if(httpResponseCode>0){
    String response = http.getString();  //Get the response to the request
  
    if (httpResponseCode == 200) {
      return true;
    } else {
      return false;
    }
  }
}

boolean ServerManager::sendData(String data) {
  HTTPClient http;
  http.begin(DATA_URL);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(data);

  if(httpResponseCode>0){
    String response = http.getString();
  
    if (httpResponseCode == 200) {
      return true;
    }
  }else{
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    return false;
  }
}

#endif
