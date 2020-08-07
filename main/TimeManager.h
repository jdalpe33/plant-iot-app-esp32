#ifndef TIME_MANAGER
#define TIME_MANAGER

#include "NTPClient.h"
#include "WiFiUdp.h"

class TimeManager {
  private:
    unsigned long currentEpoch = 0;
    WiFiUDP ntpUDP;
    NTPClient* timeClient;
    bool initialized = false;
  public:
    void initialize();
    void update();
    long getCurrentEpoch();
};

void TimeManager::initialize() {
  initialized = true;
  timeClient = new NTPClient(ntpUDP);
  timeClient->begin();
  timeClient->setTimeOffset(3600 * -4);
}

void TimeManager::update() {
  if(initialized) {
    while(!timeClient->update()) {
      timeClient->forceUpdate();
    }
  
    currentEpoch = timeClient->getEpochTime();
  }
}

long TimeManager::getCurrentEpoch() {
  return currentEpoch;
}

#endif
