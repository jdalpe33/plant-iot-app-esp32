#ifndef RELAY
#define RELAY

#include "Device.h"

class Relay {
  private:
    int pin;
  public:
    Relay(int pin) {
      this->pin = pin;
      pinMode(pin, OUTPUT);
    }
    void open();
    void close();
};

void Relay::close() {
  digitalWrite(pin, LOW);
}

void Relay::open() {
  digitalWrite(pin, HIGH);
}

#endif
