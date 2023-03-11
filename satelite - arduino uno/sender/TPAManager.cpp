#include "TPAManager.h"



TPAManager::TPAManager(struct StateInfo& stateInfo)
  : stateInfo(stateInfo) {
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /*   Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp.   oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure   oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering.   */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void TPAManager::getTPAData() {
  if (bmp.begin(0x76)) {
    stateInfo.temperature = bmp.readTemperature();
    stateInfo.pressure = bmp.readPressure();
    stateInfo.altitude = bmp.readAltitude(1018.66);
  } else {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
  }
}
