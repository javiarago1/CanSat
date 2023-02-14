#include "RadioSender.h"
#include "GPSManager.h"


struct StateInfo stateInfo;

RadioSender radioSender(stateInfo);

void setup() {
  Serial.begin(9600);
  
}

void loop() {
 
  radioSender.sendInfo();
}