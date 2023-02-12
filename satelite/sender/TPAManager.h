#ifndef TPA_MANAGER
#define TPA_MANAGER

#include <Adafruit_BMP280.h>

class TPAManager {
private:
  Adafruit_BMP280 bmp; // I2C
public:
  TPAManager();
  void getTPAData();
};



#endif