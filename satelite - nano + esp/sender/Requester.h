#ifndef REQUESTER
#define REQUESTER

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "TPAManager.h"
#include "info_structure.h"
#include <SerialTransfer.h>


struct __attribute__((packed)) ConfigData {
  float pressure;
};

class Requester {
private:
  HardwareSerial serialPort;
  SerialTransfer serialTransfer;
  const uint8_t rx2pin = 16;
  const uint8_t tx2pin = 17;
public:
  Requester();
  void requestMadridDailyPressure(TPAManager& tpaManager);
  void setupWifi(const char* ssid, const char* password);
  void sendPressureToNano(float dailiyPressure);
};



#endif