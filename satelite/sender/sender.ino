#include "RadioSender.h"

struct StateInfo stateInfo;


 RadioSender radioSender(stateInfo);

void setup() {
  Serial.begin(9600);
  
  stateInfo.latitude=3.0;
  stateInfo.longitude=4.3;
 
 
}

void loop() {
 
  radioSender.sendInfo();
}