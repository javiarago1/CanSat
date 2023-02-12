#ifndef GPS_MANAGER
#define GPS_MANAGER

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "info_structure.h"

class GPSManager {
private:

  TinyGPSPlus gps;
  SoftwareSerial GPSSerial;
  void update();
public:
  
  GPSManager(int rxPin, int txPin);
  bool getGPSInfo(struct StateInfo &);
};



#endif