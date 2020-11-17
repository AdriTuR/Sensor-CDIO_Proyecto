#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1115(0x48);

///////////////////////////////HUMIDITY
const int humidityReadPort = 0;   //Numero del puerto analogico donde va conectado el sensor de humedad

const int humidityAirValue = 30000;  // Valor en seco -- Valor de Calibracion
const int humidityWaterValue = 16825 ;  //Valor en agua -- Valor de Calibracion

///////////////////////////////SALINITY
const int salinityReadPort = 1; //Numero del puerto analogico donde va conectado el sensor de salinidad
const int salinityPowerPort = 5; //Numero del puerto donde va conectado el puerto de energia (D5)

const int salinityWaterValue = 22300; //Valor en agua sin sal, (VAire = 135) -- Valor de Calibracion

////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  ads1115.begin(); //Inicializacion de la placa ads1115
  ads1115.setGain(GAIN_ONE);

  pinMode(salinityPowerPort, OUTPUT);
}

void loop() {
  int vHumidityPort, vSalinityPort;

  //Imprime los datos por consola con un formato personalizado: pHumedad;vHumedad/pSalinidad;vHumedad  // p = porcentaje, v = valor de lectura del sensor (puerto analogico)
  //Hecho para poder recoger los datos con un formato especifico para ser leidos en la aplicacion grafica
  delay(1600);
  Serial.print(measureHumidity(vHumidityPort));  
  Serial.print(";");
  Serial.print(vHumidityPort);
  Serial.print("/");
  delay(100);
  Serial.print(measureSalinity(vSalinityPort), 2);
  Serial.print(";");
  Serial.print(vSalinityPort);
  Serial.println("");
}

//Funcion para calcular y devolver el porcentaje de la Humedad, numero entero
int measureHumidity(int &vHumidityPort) {
  int16_t val = ads1115.readADC_SingleEnded(humidityReadPort); //Lectura analogica del sensor
  int humidity = 0;
  if (val < humidityAirValue) {
    humidity = 100 * humidityAirValue / (humidityAirValue - humidityWaterValue) - val * 100 / (humidityAirValue - humidityWaterValue); //Formula usada para calcular el porcentaje segun el valor leido
    if(humidity > 100){
      humidity = 100;
    }
  }
  //Se guarda en la variable definida en el loop() (vHumidityPort) el valor de lectura para casos de Debug
  vHumidityPort = val;
  //Retorna el porcentaje
  return humidity;
}

//Funcion para calcular y devolver el porcentaje de la Humedad, con dos decimales
float measureSalinity(int &vSalinityPort) {
  digitalWrite(salinityPowerPort, HIGH); // Se activa el sensor para enviar una carga electrica
  delay(1500); // Espera de 1.5s
  int16_t val = ads1115.readADC_SingleEnded(salinityReadPort); //Se lee el valor leido del sensor
  digitalWrite(salinityPowerPort, LOW); // Se apaga el sensor tras leer la lectura
  
  float r = 0;
  if (val > salinityWaterValue) {
    r = (float)((val - salinityWaterValue) * 25.64) / 1000; //Formula usada para calcular el porcentaje segun el valor leido
    if(r > 100){
      r = 100;
    }
  }

  //Se guarda en la variable definida en el loop() (vSalinityPort) el valor de lectura para casos de Debug
  vSalinityPort = val;
  //Se devuelve el porcentaje
  return r;
}
