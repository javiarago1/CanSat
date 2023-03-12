#include "TPAManager.h"



TPAManager::TPAManager(struct StateInfo& stateInfo)
  : stateInfo(stateInfo), serialPort(2) {
  Serial.begin(9600);
  serialPort.begin(9600, SERIAL_8N1, rx2pin, tx2pin);
  serialTransfer.begin(serialPort);
}

void TPAManager::setupBMP() {
  if (!bmp.begin(0x76)) Serial.println("Could not find a valid BME280 sensor, check wiring!");
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /*   Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp.   oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure   oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering.   */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void TPAManager::getTPAData() {
  TPAState tpaState;
  uint16_t sendSize = 0;
  sendSize = serialTransfer.txObj("TPA", sendSize);
  serialTransfer.sendData(sendSize);


  if (serialTransfer.available()) {
    uint16_t recSize = 0;
    recSize = serialTransfer.rxObj(tpaState, recSize);
    if (recSize > sizeof(tpaState)) {
      stateInfo.temperature = tpaState.temperature;
      stateInfo.pressure = tpaState.pressure;
      stateInfo.humidity = tpaState.humidity;
      stateInfo.altitude = tpaState.altitude;
    } else {
      stateInfo.temperature = bmp.readTemperature();
      stateInfo.pressure = bmp.readPressure() / 100.0F;
      stateInfo.altitude = bmp.readAltitude(dailyPressure);
    }
  }
}
