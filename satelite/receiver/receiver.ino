#include "RadioReceiver.h"
#include "Serializer.h"

struct StateInfo stateInfo;

RadioReceiver radioReceiver(stateInfo);

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  if (radioReceiver.receiveInfo()){
    String jsonOfStruct;
    Serializer::stateInfo2JSONString(stateInfo,jsonOfStruct);
     Serial.println("");
    Serial.println(jsonOfStruct);
  
  }
  delay(10);
}