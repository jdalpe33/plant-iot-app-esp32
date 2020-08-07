#ifndef WATERING_CYCLE
#define WATERING_CYCLE

class WateringCycle {
  private:
    const int TOTAL_CYCLE_NUMBER = 60;
    int cycleNumber = 0;
  public:
    bool start();
    bool stop();
    void update();
    bool isRunning = false;
};

bool WateringCycle::start() {
  if(!isRunning) {
    Serial.print("Starting watering cycle for ");
    Serial.print(TOTAL_CYCLE_NUMBER);
    Serial.println(" cycles");
    cycleNumber = 0;
    isRunning = true;
    return true;
  }

  Serial.println("Cannot start, watering cycle already started");
  return false;
}

bool WateringCycle::stop() {
  if(isRunning) {
    Serial.println("Stopping watering cycle");
    isRunning = false;
    return true;
  }

  Serial.println("Cannot stop, watering cycle not running");
  return false;
}

void WateringCycle::update() {
  if(isRunning) {
    if(cycleNumber < TOTAL_CYCLE_NUMBER) {
      Serial.print("Watering cycle : ");
      Serial.print(TOTAL_CYCLE_NUMBER - cycleNumber);
      Serial.println(" left");
      cycleNumber++;
    } else {
      stop();
    }
  }
}

#endif
