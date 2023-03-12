#ifndef REQUESTER
#define REQUESTER

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "TPAManager.h"
#include "info_structure.h"

class Requester {
private:
public:
  static void requestMadridDailyPressure(TPAManager& tpaManager);
  static void setupWifi(const char* ssid, const char* password);
};



#endif