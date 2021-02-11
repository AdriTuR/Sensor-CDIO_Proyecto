// ------------------INFORMACIÓN---------------------------------------
//
// Fichero: main.ino
// Autor: LeafTech
// Fecha: 16/01/2021
//
// ------------------BIBLIOTECAS---------------------------------------
#include <Wire.h>
#include <Adafruit_ADS1015.h>

#include "SalinitySensor.h"
#include "HumiditySensor.h"
#include "TemperatureSensor.h"
#include "LuminitySensor.h"
#include "WifiManager.h"

Adafruit_ADS1115 ads1115(0x48);
WifiManager wifi;

// --------------------SET UP-----------------------------------------
void setup() {
  Serial.begin(9600);

  ads1115.begin();
  ads1115.setGain(GAIN_ONE);
}
// ---------------------LOOP------------------------------------------
void loop() {
  SalinitySensor salinitySensor(ads1115, (unsigned) 0, (unsigned) 5, (unsigned) 13500);
  HumiditySensor humiditySensor(ads1115, (unsigned) 2, (unsigned) 30000, (unsigned) 16825);
  TemperatureSensor temperatureSensor(ads1115, (unsigned) 1);
  LuminitySensor luminitySensor(ads1115, (unsigned) 3);
  
  salinitySensor.measureSalinity();
  Serial.println(salinitySensor.getVal());
  delay (300);
  humiditySensor.measureHumidity();
  Serial.println(humiditySensor.getVal());

  temperatureSensor.measureTemperature();
  Serial.println(temperatureSensor.getVal());

  luminitySensor.measureLuminity();
  Serial.println(luminitySensor.getVal());

// -----------------VALORES DE LA SONDA------------------------------
  String data[4];
  String dataName[4];
  
  dataName[0] = "Salinity";
  data[0] = salinitySensor.getVal();
  dataName[1] = "Humidity";
  data[1] = humiditySensor.getVal();
  dataName[2] = "Temperature";
  data[2] = temperatureSensor.getVal();
  dataName[3] = "Luminity";
  data[3] = luminitySensor.getVal();
  
// ---------------------WI-FI-----------------------------------------
  wifi.sendDataToCloud(dataName, data, 4);
// ---------------AHORRO DE ENERGÍA-----------------------------------
  delay(5000);
  Serial.println("Sleeping...");
  ESP.deepSleep(15 * 1000000);
}
// --------------------------------------------------------------------
