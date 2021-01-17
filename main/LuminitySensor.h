#ifndef LUMINITYSENSOR_H
#define LUMINITYSENSOR_H

#include "Sensor.h"

class LuminitySensor: public Sensor {
  public:
    void measureLuminity();
    LuminitySensor(Adafruit_ADS1115 _board, unsigned int _readPort){
      board = _board;
      analogReadPort = _readPort;
    }
};

#endif
