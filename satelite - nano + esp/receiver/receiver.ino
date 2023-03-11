#include "RadioReceiver.h"
#include "Serializer.h"
#include <SoftwareSerial.h>

struct StateInfo stateInfo;

RadioReceiver radioReceiver(stateInfo);
SoftwareSerial espSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

}

void loop() {
  if (radioReceiver.receiveInfo()){
    String jsonOfStruct;
    Serializer::stateInfo2JSONString(stateInfo,jsonOfStruct);
    Serial.println("");
    Serial.println(jsonOfStruct);
    espSerial.println(jsonOfStruct);
  
  }
  delay(10);
}