#include "Serializer.h"

void Serializer::stateInfo2JSONString(struct StateInfo& stateInfo, String& json) {
  StaticJsonDocument<200> doc;
  doc["packetNumber"] = stateInfo.packetNumber;
  doc["latitude"] = stateInfo.latitude;
  doc["longitude"] = stateInfo.longitude;
  doc["velocity"] = stateInfo.velocity;
  doc["course"] = stateInfo.course;
  serializeJson(doc, json);
}
