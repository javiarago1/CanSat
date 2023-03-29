#ifndef SERIALIZER
#define SERIALIZER

#include "info_structure.h"
#include <SoftwareSerial.h>
#include "Arduino.h"

class Serializer {
public:
   static void Serializer::printStateInfoToBothSerials(struct StateInfo& stateInfo, SoftwareSerial& espSerial);
};


#endif