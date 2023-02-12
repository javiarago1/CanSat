#include "GPSManager.h"

GPSManager::GPSManager(int rxPin, int txPin)
  : GPSSerial(rxPin, txPin) {
  GPSSerial.begin(9600);
}

void GPSManager::update() {
  while (GPSSerial.available()) {
    gps.encode(GPSSerial.read());
  }
}

bool GPSManager::getGPSInfo(struct StateInfo& gpsInfo) {
  update();
  bool isValidLocation = gps.location.isValid();
  if (isValidLocation) {
    gpsInfo.latitude = gps.location.lat();
    gpsInfo.longitude = gps.location.lng();
    gpsInfo.velocity = gps.speed.kmph();
    gpsInfo.course = gps.course.deg();
  }
  return isValidLocation;
}
