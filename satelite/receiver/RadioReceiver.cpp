#include "RadioReceiver.h"

RadioReceiver::RadioReceiver(struct StateInfo& stateInfo) : stateInfo(stateInfo){
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