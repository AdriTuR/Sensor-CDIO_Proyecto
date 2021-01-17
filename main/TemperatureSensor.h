#ifndef TEMPERATUREENSOR_H
#define TEMPERATUREENSOR_H

#include "Sensor.h"

class TemperatureSensor: public Sensor {
  public:
    void measureTemperature();
    TemperatureSensor(Adafruit_ADS1115 _board, unsigned int _readPort){
      board = _board;
      analogReadPort = _readPort;
    }
};

#endif
