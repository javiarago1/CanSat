#include "RadioSender.h"

RadioSender::RadioSender(struct StateInfo& stateInfo) : stateInfo(stateInfo){
  Serial.begin(9600);
  serialTransfer.begin(Serial);

}

void RadioSender::sendInfo() {
 if (millis() - lastSendTime >= SEND_INTERVAL) {
    packetNumber++;
    stateInfo.packetNumber = packetNumber;
    int retries = 0;
    bool success = false;
    while (retries < MAX_RETRIES && !success) {
      uint16_t sendSize = 0;
      sendSize = serialTransfer.txObj(stateInfo, sendSize);
      // Stuff buffer with array

      serialTransfer.sendData(sendSize);
      // Esperar respuesta
      unsigned long startWaitTime = millis();
      bool responseReceived = false;
      while (!responseReceived && millis() - startWaitTime < SEND_INTERVAL) {
        responseReceived = serialTransfer.available();
      }
      if (responseReceived) {
        // Procesar los datos recibidos
        Serial.println("Datos recibidos");
        lastSendTime = millis();
        success = true;
      } else {
        Serial.println("Error en el envío, reintentando...");
        retries++;
        Serial.print("Error en paquete x");
        Serial.print(" num error ");
        Serial.println(retries);
      }
    }
    if (!success) {
      lastSendTime = millis();
    }
  }
}
