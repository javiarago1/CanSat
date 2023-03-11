#include "Serializer.h"

void Serializer::stateInfo2JSONString(struct StateInfo& stateInfo, String& json) {
  StaticJsonDocument<200> doc;
  doc["packetNumber"] = stateInfo.packetNumber;
  doc["latitude"] = stateInfo.latitude;
  doc["longitude"] = stateInfo.longitude;
  doc["temperature"] = stateInfo.temperature;
  doc["pressure"] = stateInfo.pressure;
  doc["altitude"] = stateInfo.altitude;
  serializeJson(doc, json);
}
