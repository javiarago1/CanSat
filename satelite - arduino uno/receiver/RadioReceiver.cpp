#include "RadioReceiver.h"

RadioReceiver::RadioReceiver(struct StateInfo& stateInfo)
  : stateInfo(stateInfo) {
  Serial.begin(9600);
  ET.begin(details(stateInfo), &Serial);
}

bool RadioReceiver::receiveInfo() {
  if (ET.receiveData()) {
    // Procesar los datos recibidos
    // Enviar respuesta
    if (millis() - lastResponseTime >= RESPONSE_INTERVAL) {
      ET.sendData();
      lastResponseTime = millis();
    }
    return true;
  }
  return false;
}

struct PressureInfo {
  float pressure;
};

void RadioReceiver::sendPressure(SoftwareSerial& espSerial) {
  unsigned long startTime = millis();
  bool pressureReceived = false;
  serialTransfer.begin(espSerial);
  PressureInfo pressureInfo;
  while (!pressureReceived && millis() - startTime < 20000) {
    if (serialTransfer.available()) {
      uint16_t recSize = 0;
      recSize = serialTransfer.rxObj(pressureInfo, recSize);
      Serial.println("Recibido!");
      Serial.println(pressureInfo.pressure);
      stateInfo.pressure = pressureInfo.pressure;
      uint16_t sendSize = 0;
      sendSize = serialTransfer.txObj(pressureInfo, sendSize);
      serialTransfer.sendData(sendSize);
      pressureReceived = true;
    }
  }
  Serial.println("Seguimos");
  startTime = millis();
  pressureReceived = false;
  while (!pressureReceived && millis() - startTime < 20000) {
    Serial.println("Sending pressure info");
    ET.sendData();
    if (ET.receiveData()) {
      pressureReceived = true;
      Serial.println("Pressure confirmation received");
    }
    delay(500);
  }

  if (!pressureReceived) {
    Serial.println("Confirmation not received");
  }
}