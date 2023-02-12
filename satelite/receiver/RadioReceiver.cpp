#include "RadioReceiver.h"

RadioReceiver::RadioReceiver(struct StateInfo& stateInfo) : stateInfo(stateInfo){
  Serial.begin(9600);
  ET.begin(details(stateInfo), &Serial);
}

void RadioReceiver::receiveInfo() {
  if (ET.receiveData()) {
    // Procesar los datos recibidos
    Serial.print("Random 1: ");
    Serial.println(stateInfo.latitude);
    Serial.print("Random 2: ");
    Serial.println(stateInfo.longitude);
    Serial.print("Packet number : ");
    Serial.println(stateInfo.packetNumber);

    // Enviar respuesta
    if (millis() - lastResponseTime >= RESPONSE_INTERVAL) {
      ET.sendData();
      lastResponseTime = millis();
    }
  }
}