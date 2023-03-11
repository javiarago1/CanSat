#ifndef GPS_MANAGER
#define GPS_MANAGER

#include <TinyGPSPlus.h>
#include "C:\Users\JAVIER\Documents\Arduino\libraries\SoftwareSerial\SoftwareSerial.h"
#include "info_structure.h"

class GPSManager {
private:
  struct StateInfo & stateInfo;
  TinyGPSPlus gps;
  SoftwareSerial GPSSerial;
  void update();
public:
  
  GPSManager(int rxPin, int txPin, struct StateInfo & stateInfo);
  bool getGPSInfo();
};



#endif