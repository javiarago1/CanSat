#include "RadioSender.h"
#include "GPSManager.h"
#include "TPAManager.h"


struct StateInfo stateInfo;

RadioSender radioSender(stateInfo);

GPSManager gpsManager(3, 4, stateInfo);

TPAManager tpaManager(stateInfo);



void setup() {
  Serial.begin(9600);
  radioSender.readAtmosphericPressure(tpaManager);
}

void loop() {
  gpsManager.getGPSInfo();
  tpaManager.getTPAData();
  radioSender.sendInfo();
}
