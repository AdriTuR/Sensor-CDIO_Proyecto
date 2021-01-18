#include <ESP8266WiFi.h>
#include "WifiManager.h"

#define WiFi_CONNECTION_UPV
#define REST_SERVER_DWEET

#ifdef WiFi_CONNECTION_UPV //Conexion UPV
const char WiFiSSID[] = "GTI1";
const char WiFiPSK[] = "1PV.arduino.Toledo";
#else //Conexion fuera de la UPV
const char WiFiSSID[] = "";//Nombre de la red Wi-Fi 
const char WiFiPSK[] = "";//Contraseña de la red Wi-Fi
#endif

#if defined(WiFi_CONNECTION_UPV) //Conexion UPV
const char Server_Host[] = "proxy.upv.es";
const int Server_HttpPort = 8080;
#elif defined(REST_SERVER_DWEET) //Conexion fuera de la UPV
const char Server_Host[] = "dweet.io";
const int Server_HttpPort = 80;
#endif

WiFiClient client;

WifiManager::WifiManager() {
  connectWiFi();
  pinMode(4, OUTPUT);
}

void WifiManager::sendDataToCloud(String fieldName[], String data[], int nFields) {
  if(!isWifiConnected()){
    connectWiFi();
    unsigned int tries = 0;
    //Max. 7 veces para intentar conectarse a la wifi
    while (!isWifiConnected()) {
      if(tries >= 7){
        return;
      }
      tries++;
      Serial.println("Wifi Off... Reconnecting... (" + (String) tries + ")");
      delay(8000);
    }
  }else{
    Serial.println("WiFi connected");
  }
  HTTPPost(fieldName, data, nFields);
}

void WifiManager::connectWiFi()
{
  WiFi.begin(WiFiSSID, WiFiPSK);
}

bool WifiManager::isWifiConnected() {
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(4, HIGH);
    return true;
  } else {
    digitalWrite(4, LOW);
    return false;
  }
}

void WifiManager::blinkLedStatus() {
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(4, HIGH);
}

void WifiManager::HTTPPost(String fieldName[], String fieldData[], int numFields) {
  if (client.connect( Server_Host , Server_HttpPort )) {
    Serial.println("POST data to REST services");
    String PostData = "";
    for ( int field = 0; field < numFields; field++ ) {
      PostData += fieldName[field] + "=" + fieldData[ field ];
      if (field <= numFields) {
        PostData += "&";
      }
    }
    client.println( "POST http://dweet.io/dweet/for/cdiocurso2020g09?");
    client.println( "Host: dweet.io");
    client.println( "Connection: close" );
    client.println( "Content-Type: application/x-www-form-urlencoded" );
    client.println( "Content-Length: " + String( PostData.length() ) );
    client.println();
    client.println(PostData);
    
    for(int i = 0; i < 4; i++){
      blinkLedStatus();
      delay(100);
    }

    delay(500);
    Serial.println();
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    Serial.println();
    Serial.println();

  } else {
    Serial.println("Can't connect with REST services");
  }
}
