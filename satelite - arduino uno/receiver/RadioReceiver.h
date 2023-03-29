#ifndef RADIO_RECEIVER
#define RADIO_RECEIVER

#include <EasyTransfer.h>
#include "info_structure.h"
#include <SoftwareSerial.h>
#include <SerialTransfer.h>


class RadioReceiver {
private:
  struct StateInfo &stateInfo;
  EasyTransfer ET;
  SerialTransfer serialTransfer;
  const int RESPONSE_INTERVAL = 1000;  // Intervalo de tiempo para enviar respuesta (en milisegundos)
  unsigned long lastResponseTime = 0;
public:
  RadioReceiver(struct StateInfo &);
  bool receiveInfo();
  void sendPressure(SoftwareSerial& espSerial);
};


#endif