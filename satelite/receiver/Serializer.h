#ifndef SERIALIZER
#define SERIALIZER

#include <ArduinoJson.h>
#include "info_structure.h"


class Serializer {
public:
   static void Serializer::stateInfo2JSONString(struct StateInfo& stateInfo, String& json);
};


#endif