#ifndef SERVER_MANAGER
#define SERVER_MANAGER

#include "HTTPClient.h"
#include "Variables.h"

class ServerManager {
  private:
  public:
    boolean sendData(String data);
};

boolean ServerManager::sendData(String data) {
  HTTPClient http;
  http.begin(DATA_URL);//"http://localhost:3000/addlog"); //Specify destination for HTTP request
  http.addHeader("Content-Type", "application/json"); //Specify content-type header

  int httpResponseCode = http.POST(data); //Send the actual POST request

  if(httpResponseCode>0){
  String response = http.getString();  //Get the response to the request
  Serial.println(httpResponseCode);   //Print return code
  Serial.println(response);           //Print request answer

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
