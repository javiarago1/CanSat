#include "RadioSender.h"
#include "GPSManager.h"
#include "TPAManager.h"
#include "Requester.h"
 
struct StateInfo stateInfo;

RadioSender radioSender(stateInfo);

GPSManager gpsManager(stateInfo);

TPAManager tpaManager(stateInfo);

void setup() {
  tpaManager.setupBMP();
  Requester::setupWifi("DIGIFIBRA-y54u", "zKxYbSfcEF");
  Requester::requestMadridDailyPressure(tpaManager);
  Requester::sendPressureToNano();
  Serial.begin(9600);
}

void loop() {
  Serial.println(tpaManager.dailyPressure);
  tpaManager.getTPAData();
  gpsManager.getGPSInfo();
  radioSender.sendInfo();
  delay(1000);
}

