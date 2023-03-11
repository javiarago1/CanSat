#include "RadioReceiver.h"

RadioReceiver::RadioReceiver(struct StateInfo& stateInfo)
  : stateInfo(stateInfo) {
  Serial.begin(9600);
  serialTransfer.begin(Serial);
}

bool RadioReceiver::receiveInfo() {

  if (serialTransfer.available()) {
    // use this variable to keep track of how many
    // bytes we've processed from the receive buffer
    uint16_t recSize = 0;

    recSize = serialTransfer.rxObj(stateInfo, recSize);
    char ack[] = "ACK";
    uint16_t confirmSize = 0;
    confirmSize = serialTransfer.txObj(ack, confirmSize);
    serialTransfer.sendData(confirmSize);
    return true;
    // Send "ACK" to confirm delivery

  }
  return false;
}