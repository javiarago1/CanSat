#include "RadioSender.h"
#include "GPSManager.h"
#include "TPAManager.h"



struct StateInfo stateInfo;

RadioSender radioSender(stateInfo);

GPSManager gpsManager(stateInfo);

TPAManager tpaManager(stateInfo);


void setup() {
  Serial.begin(9600);
}

void loop() {
  tpaManager.getTPAData();
  gpsManager.getGPSInfo();
  radioSender.sendInfo();
  delay(1000);
}

