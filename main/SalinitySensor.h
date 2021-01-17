#ifndef SALINITYSENSOR_H
#define SALINITYSENSOR_H

#include "Sensor.h"

class SalinitySensor: public Sensor {
  private:
    unsigned int salinityWaterValue;
  public:
    void measureSalinity();
    SalinitySensor(Adafruit_ADS1115 _board, unsigned int _readPort, unsigned int _powerPort, unsigned int _salinityWaterValue){
      board = _board;
      analogReadPort = _readPort;
      powerPort = _powerPort;
      salinityWaterValue = _salinityWaterValue;
      pinMode(powerPort, OUTPUT);
     }
};

#endif
