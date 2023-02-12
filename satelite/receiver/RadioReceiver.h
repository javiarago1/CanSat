#ifndef RADIO_RECEIVER
#define RADIO_RECEIVER

#include <EasyTransfer.h>
#include "info_structure.h"

class RadioReceiver {
private:
  struct StateInfo & stateInfo;
  EasyTransfer ET;
  const int RESPONSE_INTERVAL = 1000;  // Intervalo de tiempo para enviar respuesta (en milisegundos)
  unsigned long lastResponseTime = 0; 
public:
  RadioReceiver(struct StateInfo &);
  void receiveInfo();
};


#endif