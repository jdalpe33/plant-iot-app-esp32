#ifndef SENSOR
#define SENSOR

class Sensor {
  protected:
    int value = -1;
  public:
    virtual void readValue() = 0;
    int getValue() { return value; }
};

#endif
