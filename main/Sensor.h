#ifndef SENSOR_H
#define SENSOR_H
#include <Adafruit_ADS1015.h>

class Sensor {
  protected:
    Adafruit_ADS1115 board;
    unsigned int analogReadPort;
    unsigned int powerPort;
    int readedValue;
    int finalValue;
    void readValue();
  public:
    int getVal(){
      return finalValue;
    };
    int getValLect(){
      return readedValue;
    }; 
};

#endif
