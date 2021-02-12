// ------------------INFORMACIÓN---------------------------------------
//
// Fichero: TemperatureSensor.h
// Autor: LeafTech
// Fecha: 16/01/2021
//
// ---------------------------------------------------------------------
#ifndef TEMPERATUREENSOR_H
#define TEMPERATUREENSOR_H
// ------------------BIBLIOTECAS----------------------------------------
#include "Sensor.h"
// ----------------CLASE TEMPERATURESENSOR------------------------------
class TemperatureSensor: public Sensor {
  public:
    void measureTemperature();
    TemperatureSensor(Adafruit_ADS1115 _board, unsigned int _readPort){
      board = _board;
      analogReadPort = _readPort;
    }
};
// ---------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------
