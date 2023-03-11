#ifndef GPS_MANAGER
#define GPS_MANAGER

#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include "info_structure.h"

class GPSManager {
private:
  struct StateInfo & stateInfo;
  TinyGPSPlus gps;
  HardwareSerial GPSSerial;
  void update();
public:
  
  GPSManager(struct StateInfo & stateInfo);
  bool getGPSInfo();
};



#endif