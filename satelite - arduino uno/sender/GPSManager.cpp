#include "GPSManager.h"

GPSManager::GPSManager(int rxPin, int txPin, struct StateInfo& stateInfo)
  : GPSSerial(rxPin, txPin), stateInfo(stateInfo) {
  GPSSerial.begin(9600);
}

void GPSManager::update() {
  while (GPSSerial.available()) {
    gps.encode(GPSSerial.read());
  }
}

bool GPSManager::getGPSInfo() {
  update();
  bool isValidLocation = gps.location.isValid();
  if (isValidLocation) {
    stateInfo.latitude = gps.location.lat();
    stateInfo.longitude = gps.location.lng();
  }
  return isValidLocation;
}
