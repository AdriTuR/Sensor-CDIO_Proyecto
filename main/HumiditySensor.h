// ------------------INFORMACIÓN---------------------------------------
//
// Fichero: HumiditySensor.h
// Autor: LeafTech
// Fecha: 16/01/2021
//
// ---------------------------------------------------------------------
#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H
// ------------------BIBLIOTECAS----------------------------------------
#include "Sensor.h"
// ----------------CLASE HUMIDITYSENSOR---------------------------------
class HumiditySensor: public Sensor {
  private:
    unsigned int humidityAirValue;
    unsigned int humidityWaterValue;
  public:
    void measureHumidity();
    HumiditySensor(Adafruit_ADS1115 _board, unsigned int _readPort, unsigned int _humidityAirValue, unsigned int _humidityWaterValue){
      board = _board;
      analogReadPort = _readPort;
      humidityAirValue = _humidityAirValue;
      humidityWaterValue = _humidityWaterValue;
    }
};
// ---------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------
