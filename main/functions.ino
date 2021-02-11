// ------------------INFORMACIÓN---------------------------------------
//
// Fichero: WifiManager.ino
// Autor: LeafTech
// Fecha: 16/01/2021
// ------------------BIBLIOTECAS----------------------------------------
#include "SalinitySensor.h"
#include "HumiditySensor.h"
#include "TemperatureSensor.h"
#include "LuminitySensor.h"
// ---------------MEASURE SALINITY--------------------------------------
void SalinitySensor::measureSalinity() {
  digitalWrite(powerPort, HIGH); // Se activa el sensor para enviar una carga electrica
  delay(1500); // Espera de 1.5s
  int16_t val = board.readADC_SingleEnded(analogReadPort); //Se lee el valor leido del sensor
  digitalWrite(powerPort, LOW); // Se apaga el sensor tras leer la lectura

  float r = 0;
  if (val > salinityWaterValue) {
    r = (float)((val - salinityWaterValue) * 25.64) / 1000; //Formula usada para calcular el porcentaje segun el valor leido
    if (r > 100) {
      r = 100;
    }
  }

  //Se guarda en la variable definida en el loop() (vSalinityPort) el valor de lectura para casos de Debug
  readedValue = val;
  //Se devuelve el porcentaje
  finalValue = r;
}
// ------------------------MEASURE HUMIDITY-----------------------------
void HumiditySensor:: measureHumidity() {
  int16_t val = board.readADC_SingleEnded(analogReadPort); //Lectura analogica del sensor
  int humidity = 0;
  if (val < humidityAirValue) {
    humidity = 100 * humidityAirValue / (humidityAirValue - humidityWaterValue) - val * 100 / (humidityAirValue - humidityWaterValue); //Formula usada para calcular el porcentaje segun el valor leido
    if (humidity > 100) {
      humidity = 100;
    }
  }
  //Se guarda en la variable definida en el loop() (vHumidityPort) el valor de lectura para casos de Debug
  readedValue = val;
  //Retorna el porcentaje
  finalValue = humidity;
}
// --------------------MEASURE TEMPERATURE--------------------------------
void TemperatureSensor::measureTemperature() {
  int16_t val = board.readADC_SingleEnded(analogReadPort); //Valor leido del sensor de temperatura
  float Vo = (((float)val / 1000.0) / 8.0); //Fórmula para calcular el voltaje
  float temperature = (Vo - 0.79) / 0.034; //Fórmula para calcular la temperatura en base a Vo dandola en Celsius
  
  readedValue = val;
  finalValue = temperature;
  //Retorna la temperatura
}
// --------------------MEASURE LUMINIDTY--------------------------------
void LuminitySensor::measureLuminity(){
  int16_t val = board.readADC_SingleEnded(analogReadPort); //Valor leido del sensor de iluminación
  readedValue = val;
 
 //Si el valor leido por el sensor es menor de 50 muestra en pantalla que es de noche
   if(val>15540){ 
    
    finalValue = 0; //Asignamos el numero 0 para que en la interfaz grafica muestre de noche
  }
  //Si el valor leido por el sensor se encuentra entre 50 y 150  muestra en pantalla que esta nublado
  else if  (val<=15540 && val<=15480){
  
    finalValue = 1; //Asignamos el numero 1 para que en la interfaz grafica muestre nublado
  }
  //Si el valor leido por el sensor es mayor de 150  muestra en pantalla que esta soleado
  else {
    
    finalValue = 2; //Asignamos el numero 1 para que en la interfaz grafica muestre soleado

  }
   
}
