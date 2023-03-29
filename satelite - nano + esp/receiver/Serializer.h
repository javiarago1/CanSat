#ifndef SERIALIZER
#define SERIALIZER


#include "info_structure.h"
#include "Arduino.h"


class Serializer {
public:
  static void stateInfo2JSONString(struct StateInfo& stateInfo, String& json);
};


#endif