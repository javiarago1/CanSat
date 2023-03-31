#include "RadioReceiver.h"
#include "Serializer.h"
#include <SoftwareSerial.h>

struct StateInfo stateInfo;

RadioReceiver radioReceiver(stateInfo);
SoftwareSerial espSerial(2, 3);  // RX, TX

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
}

int prevPacket = -1;

void loop() {
  if (radioReceiver.receiveInfo()) {
    if (stateInfo.packetNumber != prevPacket) {
      String jsonOfStruct;
      Serializer::stateInfo2JSONString(stateInfo, jsonOfStruct);
      espSerial.println(jsonOfStruct);
      Serial.println(jsonOfStruct);
    }
    prevPacket = stateInfo.packetNumber;
  }
  delay(10);
}