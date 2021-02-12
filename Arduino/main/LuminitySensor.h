// ------------------INFORMACIÓN---------------------------------------
//
// Fichero: LuminitySensor.h
// Autor: LeafTech
// Fecha: 16/01/2021
//
// ---------------------------------------------------------------------
#ifndef LUMINITYSENSOR_H
#define LUMINITYSENSOR_H
// ------------------BIBLIOTECAS----------------------------------------
#include "Sensor.h"
// ----------------CLASE LUMINITYSENSOR---------------------------------
class LuminitySensor: public Sensor {
  public:
    void measureLuminity();
    LuminitySensor(Adafruit_ADS1115 _board, unsigned int _readPort){
      board = _board;
      analogReadPort = _readPort;
    }
};
// ---------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------
