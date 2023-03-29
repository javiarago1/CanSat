#ifndef TPA_MANAGER
#define TPA_MANAGER


#include "info_structure.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>


class TPAManager {
private:
  struct StateInfo& stateInfo;
  Adafruit_BMP280 bmp;  // I2C
  float prevAltitude;
  bool hasAscended;
  bool firstTime;
public:
  double dailyPressure = 1021;
  TPAManager(struct StateInfo& stateInfo);
  void getTPAData();
};



#endif