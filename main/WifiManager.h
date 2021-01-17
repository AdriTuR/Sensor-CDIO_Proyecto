#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

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

#endif
