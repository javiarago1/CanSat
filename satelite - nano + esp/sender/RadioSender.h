#ifndef RADIO_SENDER
#define RADIO_SENDER

#include <SerialTransfer.h>
#include "info_structure.h"

class RadioSender {
private:
  SerialTransfer serialTransfer;
  struct StateInfo &stateInfo;
  float packetNumber;
  const int SEND_INTERVAL = 1000;
  const int MAX_RETRIES = 3;
  unsigned long lastSendTime = 0;
public:
  RadioSender(struct StateInfo &);
  void sendInfo();
};


#endif