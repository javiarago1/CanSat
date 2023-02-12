#include "TPAManager.h"



TPAManager::TPAManager() {
  int numOfTries = 0;
  while (!bmp.begin() && numOfTries < 5) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    numOfTries++;
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /*   Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp.   oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure   oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering.   */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void TPAManager::getTPAData() {
  float f = bmp.readTemperature();  //Conversion   from C to F
  Serial.print(F("Temperature = "));
  Serial.println(f);

  float P = bmp.readPressure();  //displaying the Pressure in inches of mercury, you can change the unit
  Serial.print(F("Pressure   = "));
  Serial.print(P);

  float A = bmp.readAltitude(1036.43);  //The "1019.66" is the pressure(hPa)   at sea level in day in your region
  Serial.print(F("Approx altitude = "));          //If you don't know it, modify it until you get your current altitude
  Serial.print(A);

  Serial.println();
}


