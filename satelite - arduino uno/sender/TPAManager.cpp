#include "TPAManager.h"



TPAManager::TPAManager(struct StateInfo& stateInfo)
  : stateInfo(stateInfo) {
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /*   Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp.   oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure   oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering.   */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

const int windowSize = 10;
float altitudeWindow[windowSize];
int currentWindowIndex = 0;


void TPAManager::getTPAData() {
  if (bmp.begin(0x76)) {
    stateInfo.temperature = bmp.readTemperature();
    stateInfo.pressure = bmp.readPressure();
    stateInfo.altitude = bmp.readAltitude(dailyPressure);


    if (!firstTime) {
      prevAltitude = stateInfo.altitude;
      firstTime = true;
    }
    // Comprobar si se ha subido o bajado
    if (stateInfo.altitude - prevAltitude > 1) {  // si la diferencia es mayor que 0.75 m
      hasAscended = true;
      prevAltitude = stateInfo.altitude;
      hasAscended = true;
    } else if (hasAscended && prevAltitude - stateInfo.altitude > 1) {  // si ya se ha subido y la diferencia es mayor que 0.75 m
      // Encender el LED
      pinMode(13, OUTPUT);
      digitalWrite(13, HIGH);
      hasAscended = false;  // reiniciar la variable
    }


    // Actualizar el estado de la altitud
    if (hasAscended) {
      stateInfo.altitudeStatus = 1;  // si ha subido, se considera una subida
    } else {
      stateInfo.altitudeStatus = 0;  // si no ha habido cambios, se considera en el mismo nivel
    }



  } else {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
  }
}
