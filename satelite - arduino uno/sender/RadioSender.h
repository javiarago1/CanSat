#ifndef RADIO_SENDER
#define RADIO_SENDER

#include <EasyTransfer.h>
#include "info_structure.h"
#include "TPAManager.h"



class RadioSender {
private:
  EasyTransfer ET;
  struct StateInfo &stateInfo;
  int packetNumber;
  const int SEND_INTERVAL = 1000;
  const int MAX_RETRIES = 3;
  unsigned long lastSendTime = 0;
public:
  RadioSender(struct StateInfo &);
  void sendInfo();
  void readAtmosphericPressure(TPAManager & tpaManager);
};


#endif