#include "RadioSender.h"
#include "GPSManager.h"
#include "TPAManager.h"
#include "Requester.h"

struct StateInfo stateInfo;

RadioSender radioSender(stateInfo);

GPSManager gpsManager(stateInfo);

TPAManager tpaManager(stateInfo);

Requester requester;

void setup() {
  tpaManager.setupBMP();
  requester.setupWifi("DIGIFIBRA-y54u", "zKxYbSfcEF");
  requester.requestMadridDailyPressure(tpaManager);
  requester.sendPressureToNano(tpaManager.dailyPressure);
  Serial.begin(9600);
}

void loop() {
  tpaManager.getTPAData();
  gpsManager.getGPSInfo();
  radioSender.sendInfo();
  delay(1000);
}
