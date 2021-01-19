// ------------------INFORMACIÓN---------------------------------------
//
// Fichero: WifiManager.h
// Autor: LeafTech
// Fecha: 16/01/2021
//
// ---------------------------------------------------------------------
#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H
// ----------------CLASE WIFIMANAGER------------------------------------
class WifiManager{
  public:
    WifiManager();
    void sendDataToCloud(String fieldName[], String data[], int nFields);
    bool isWifiConnected();
  private:
    void connectWiFi();
    void blinkLedStatus();
    void HTTPPost(String fieldName[], String fieldData[], int numFields); 
};
// ---------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------
