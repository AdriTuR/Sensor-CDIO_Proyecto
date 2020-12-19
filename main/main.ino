#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1115(0x48);

///////////////////////////////HUMIDITY//////////////////////////////////////////////////////////////////////////
const int humidityAirValue = 30000;  // Valor en seco -- Valor de Calibracion
const int humidityWaterValue = 16825 ;  //Valor en agua -- Valor de Calibracion

///////////////////////////////SALINITY//////////////////////////////////////////////////////////////////////////
const int salinityWaterValue = 8600; //Valor en agua sin sal, (VAire = 135) -- Valor de Calibracion

void setup() {
  Serial.begin(9600);

  ads1115.begin(); //Inicializacion de la placa ads1115
  ads1115.setGain(GAIN_ONE);
}

void loop() {
  int vHumidityPort, vSalinityPort, vTemperaturePort;

  //Imprime los datos por consola con un formato personalizado: pHumedad;vHumedad/pSalinidad;vHumedad/pTemperatura;vTemperatura
  // p = porcentaje, v = valor de lectura del sensor (puerto analogico)
  //Hecho para poder recoger los datos con un formato especifico para ser leidos en la aplicacion grafica
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
  Serial.println("");
 
}

////////////////////////Funcion para calcular y devolver el porcentaje de la Humedad, numero entero///////////////////////////////////////////
int measureHumidity(int &vHumidityPort, int humidityReadPort) {
  int16_t val = ads1115.readADC_SingleEnded(humidityReadPort); //Lectura analogica del sensor
  int humidity = 0;
  if (val < humidityAirValue) {
    humidity = 100 * humidityAirValue / (humidityAirValue - humidityWaterValue) - val * 100 / (humidityAirValue - humidityWaterValue); //Formula usada para calcular el porcentaje segun el valor leido
    if (humidity > 100) {
      humidity = 100;
    }
  }
  //Se guarda en la variable definida en el loop() (vHumidityPort) el valor de lectura para casos de Debug
  vHumidityPort = val;
  //Retorna el porcentaje
  return humidity;
}

////////////////////////////////Funcion para calcular y devolver el porcentaje de la Salinidad, con dos decimales/////////////////////////////////
float measureSalinity(int &vSalinityPort, int salinityReadPort, int salinityPowerPort) {
  pinMode(salinityPowerPort, OUTPUT);
  digitalWrite(salinityPowerPort, HIGH); // Se activa el sensor para enviar una carga electrica
  delay(1500); // Espera de 1.5s
  int16_t val = ads1115.readADC_SingleEnded(salinityReadPort); //Se lee el valor leido del sensor
  digitalWrite(salinityPowerPort, LOW); // Se apaga el sensor tras leer la lectura

  float r = 0;
  if (val > salinityWaterValue) {
    r = (float)((val - salinityWaterValue) * 25.64) / 1000; //Formula usada para calcular el porcentaje segun el valor leido
    if (r > 100) {
      r = 100;
    }
  }

  //Se guarda en la variable definida en el loop() (vSalinityPort) el valor de lectura para casos de Debug
  vSalinityPort = val;
  //Se devuelve el porcentaje
  return r;
}

/////////////////////////Funcion para calcular y devolver la Temperatura en Celsius, con dos decimales////////////////////////////////////////////////
int measureTemperature(int &vTemperaturePort, int temperatureReadPort) {
  int16_t val = ads1115.readADC_SingleEnded(temperatureReadPort); //Se lee el valor leido del sensor
  float Vo = (((float)val / 1000.0) / 8.0); //Fórmula para calcular el voltaje
  float temperature = (Vo - 0.79) / 0.034; //Fórmula para calcular la temperatura en base a Vo dandola en Celsius
  vTemperaturePort = val;
  
  return temperature;
  //Retorna la temperatura
}

////////////////////////Funcion para calcular y devolver el Nivel de Luz/////////////////////////////////////////////////////////////////////////////
