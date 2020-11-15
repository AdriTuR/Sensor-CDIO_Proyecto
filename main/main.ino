#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1115(0x48);

///////////////////////////////HUMIDITY
const int humidityReadPort = 0;

const int humidityAirValue = 30000;  // Medimos valor en seco
const int humidityWaterValue = 16825 ;  // Medimos valor en agua

///////////////////////////////SALINITY
const int salinityReadPort = 1;
const int salinityPowerPort = 5;

const int salinityWaterValue = 22300; //Valor en agua sin sal, VAire = 135

////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  ads1115.begin(); //Initialize ads1115
  ads1115.setGain(GAIN_ONE);

  pinMode(salinityPowerPort, OUTPUT);
}

void loop() {
  int vHumidityPort, vSalinityPort;
  
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

int measureHumidity(int &vHumidityPort) {
  int16_t val = ads1115.readADC_SingleEnded(humidityReadPort);
  int humidity;
  if (val >= humidityAirValue) {
    humidity = 0;
  } else {
    humidity = 100 * humidityAirValue / (humidityAirValue - humidityWaterValue) - val * 100 / (humidityAirValue - humidityWaterValue);
  }
  vHumidityPort = val;
  return humidity;
}

float measureSalinity(int &vSalinityPort) {
  digitalWrite(salinityPowerPort, HIGH); // Turn on the sensor
  delay(1500);
  int16_t val = ads1115.readADC_SingleEnded(salinityReadPort);
  digitalWrite(salinityPowerPort, LOW); // Turn off the sensor
  
  float r = 0;
  if (val > salinityWaterValue) {
    r = (float)((val - salinityWaterValue) * 9.553) / 1000;
  }
  vSalinityPort = val;
  return r;
}
