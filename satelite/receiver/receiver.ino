#include "RadioReceiver.h"

struct StateInfo stateInfo;

RadioReceiver radioReceiver(stateInfo);

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  
  radioReceiver.receiveInfo();
  // Esperar un tiempo antes de recibir más datos
  delay(10);
}