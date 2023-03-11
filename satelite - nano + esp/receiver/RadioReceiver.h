#ifndef RADIO_RECEIVER
#define RADIO_RECEIVER

#include <SerialTransfer.h>
#include "info_structure.h"

class RadioReceiver {
private:
  struct StateInfo & stateInfo;
  SerialTransfer serialTransfer;
public:
  RadioReceiver(struct StateInfo &);
  bool receiveInfo();
};


#endif