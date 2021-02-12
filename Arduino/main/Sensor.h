// ------------------INFORMACIÓN---------------------------------------
//
// Fichero: Sensor.h
// Autor: LeafTech
// Fecha: 16/01/2021
//
// ---------------------------------------------------------------------
#ifndef SENSOR_H
#define SENSOR_H
// ------------------BIBLIOTECAS----------------------------------------
#include <Adafruit_ADS1015.h>
// -----------------CLASE SENSOR----------------------------------------
class Sensor {
  protected:
    Adafruit_ADS1115 board;
    unsigned int analogReadPort;//Puerto analógico del ADS
    unsigned int powerPort;//Puerto de alimentación 
    int readedValue;//Valor de lectura 
    int finalValue;//Valor de lectura 
    void readValue();
  public:
    int getVal(){  //Método para obtener valor final
      return finalValue;
    };
    int getValLect(){ //Método para obtener el valor de lectura
      return readedValue;
    }; 
};
// ---------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------
