#include <Wire.h>
#include <Adafruit_ADS1015.h>

#include "SalinitySensor.h"
#include "HumiditySensor.h"
#include "TemperatureSensor.h"
#include "LuminitySensor.h"
#include "WifiManager.h"

Adafruit_ADS1115 ads1115(0x48);
WifiManager wifi;

SalinitySensor salinitySensor(ads1115, (unsigned) 1, (unsigned) 5, (unsigned) 8600);
HumiditySensor humiditySensor(ads1115, (unsigned) 0, (unsigned) 30000, (unsigned) 16825);
TemperatureSensor temperatureSensor(ads1115, (unsigned) 3);
LuminitySensor luminitySensor(ads1115, (unsigned) 2);

void setup() {
  Serial.begin(9600);

  ads1115.begin(); //Inicializacion de la placa ads1115
  ads1115.setGain(GAIN_ONE);
}

void loop() {
  salinitySensor.measureSalinity();
  //Serial.println(salinitySensor.getVal());

  humiditySensor.measureHumidity();
  //Serial.println(humiditySensor.getVal());

  temperatureSensor.measureTemperature();
  //Serial.println(temperatureSensor.getVal());

  luminitySensor.measureLuminity();
  //Serial.println(luminitySensor.getVal());
  
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

  
  wifi.sendDataToCloud(dataName, data, 4);

  delay(5000);
  Serial.println("Sleeping...");
  ESP.deepSleep(30 * 1000000);
  
  
  //Imprime los datos por consola con un formato personalizado: pHumedad;vHumedad/pSalinidad;vHumedad/pTemperatura;vTemperatura/Iluminación;vIluminación;
  // p = porcentaje, v = valor de lectura del sensor (puerto analogico)
  //Hecho para poder recoger los datos con un formato especifico para ser leidos en la aplicacion grafica
  /*
  Serial.print(measureSalinity(vSalinityPort, 1, 5), 2);
  Serial.print(";");
  Serial.print(vSalinityPort);
  Serial.print("/");
 
  Serial.print(measureHumidity(vHumidityPort, 0));
  Serial.print(";");
  Serial.print(vHumidityPort);
  Serial.print("/");

  Serial.print(measureTemperature(vTemperaturePort, 3));
  Serial.print(";");
  Serial.print(vTemperaturePort);
  Serial.print("/");
  
  Serial.print(measureLuminity(vLuminityPort,2 ));
  Serial.print(";");
  Serial.print(vLuminityPort);
  Serial.println("");
  */
 
}
