#include "TPAManager.h"



TPAManager::TPAManager(struct StateInfo& stateInfo)
  : stateInfo(stateInfo), serialPort(2) {
  Serial.begin(9600);
  serialPort.begin(9600, SERIAL_8N1, rx2pin, tx2pin);
  serialTransfer.begin(serialPort);
}

void TPAManager::getTPAData() {
  TPAState tpaState;
  uint16_t sendSize = 0;
  sendSize = serialTransfer.txObj("wassap", sendSize);
  serialTransfer.sendData(sendSize);
  if (serialTransfer.available()) {
    uint16_t recSize = 0;
    recSize = serialTransfer.rxObj(tpaState, recSize);
    stateInfo.temperature = tpaState.temperature;
    stateInfo.pressure = tpaState.pressure;
    stateInfo.humidity = tpaState.humidity;
    stateInfo.altitude = tpaState.altitude;
  } 
}
