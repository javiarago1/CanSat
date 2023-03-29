#include "RadioReceiver.h"
#include "Serializer.h"
#include <SoftwareSerial.h>

struct StateInfo stateInfo;

RadioReceiver radioReceiver(stateInfo);
SoftwareSerial espSerial(2, 3);  // RX, TX

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  radioReceiver.sendPressure(espSerial);
}

void loop() {
  if (radioReceiver.receiveInfo()) {
    Serializer::printStateInfoToBothSerials(stateInfo, espSerial);
  }
  delay(10);
}