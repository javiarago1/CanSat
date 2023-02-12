#include "RadioSender.h"

RadioSender::RadioSender(struct StateInfo& stateInfo) : stateInfo(stateInfo){
  Serial.begin(9600);
  ET.begin(details(stateInfo), &Serial);

}

void RadioSender::sendInfo() {
  if (millis() - lastSendTime >= SEND_INTERVAL) {
    packetNumber++;
    stateInfo.packetNumber=packetNumber;
    int retries = 0;
    bool success = false;
    while (retries < MAX_RETRIES && !success) {
      ET.sendData();
      // Esperar respuesta
      unsigned long startWaitTime = millis();
      bool responseReceived = false;
      while (!responseReceived && millis() - startWaitTime < SEND_INTERVAL) {
        responseReceived = ET.receiveData();
      }
      if (responseReceived) {
        // Procesar los datos recibidos
        Serial.println("Datos recibidos");
        lastSendTime = millis();
        success = true;
      } else {
        Serial.println("Error en el envío, reintentando...");
        retries++;
        Serial.print("Error en paquete ");
        Serial.print(packetNumber);
        Serial.print(" num error ");
        Serial.println(retries);
      }
    }
    if (!success){
      lastSendTime= millis();
    }
  }
}
