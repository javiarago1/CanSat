#ifndef TPA_MANAGER
#define TPA_MANAGER


#include "info_structure.h"
#include <HardwareSerial.h>
#include <SerialTransfer.h>

struct __attribute__((packed)) TPAState {
  float pressure;
  float temperature;
  float humidity;
  float altitude;
};

class TPAManager {
private:
  HardwareSerial serialPort;
  struct StateInfo & stateInfo;
  const uint8_t rx2pin = 16;
  const uint8_t tx2pin = 17;
  SerialTransfer serialTransfer;
public:
  TPAManager(struct StateInfo & stateInfo);
  void getTPAData();
};



#endif