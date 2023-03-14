#include "tpa_structure.h"
#include <SerialTransfer.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_HS300x.h>

struct TPAState tpaState;

SerialTransfer serialTransfer;

float pressureAtSeaLevel = 1020.25;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  if (!HS300x.begin()) Serial.println("Failed to initialize humidity temperature sensor!");
  if (!BARO.begin()) Serial.println("Failed to initialize pressure sensor!");
  serialTransfer.begin(Serial1);
  receivePressure();
}

char arr[6];

void loop() {
  if (serialTransfer.available()) {
    uint16_t recSize = 0;
    recSize = serialTransfer.rxObj(arr, recSize);
    if (strcmp(arr, "TPA") == 0) {
      Serial.println(arr);
      getTPAData();
      sendData();
    }
  }
}

float old_temp = 0;

float old_hum = 0;


void getTPAData() {
  float temperature = HS300x.readTemperature();
  float humidity = HS300x.readHumidity();
  if (abs(old_temp - temperature) >= 0.5 || abs(old_hum - humidity) >= 1) {
    tpaState.temperature = temperature;
    tpaState.humidity = humidity;
  }

  float pressure = BARO.readPressure();
  pressure *= 10;
  tpaState.pressure = pressure;
  float altitude = 44330 * (1.0 - pow(pressure / pressureAtSeaLevel, 0.1903));
  tpaState.altitude = altitude;
}


void sendData() {
  uint16_t sendSize = 0;
  sendSize = serialTransfer.txObj(tpaState, sendSize);
  serialTransfer.sendData(sendSize);
}


void receivePressure() {
  unsigned long startTime = millis();
  ConfigData configData;
  bool received = false;
  while (millis() - startTime < 20000 && !received) {
    if (serialTransfer.available()) {
      Serial.println("Configuration of pressure correctly");
      Serial.print("Pressure ");
      uint16_t recSize = 0;
      recSize = serialTransfer.rxObj(configData, recSize);
      Serial.println(configData.pressure);
      uint16_t sendSize = 0;
      sendSize = serialTransfer.txObj("REC", sendSize);
      serialTransfer.sendData(sendSize);
      received = true;
    }
    delay(1000);
  }
}
