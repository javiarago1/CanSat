#include "Serializer.h"

// Not using ArduinoJSON because of problems of optimization

void Serializer::stateInfo2JSONString(struct StateInfo& stateInfo, String& json) {
  json = "{";
  json += "\"packetNumber\":" + String(stateInfo.packetNumber) + ",";
  json += "\"latitude\":" + String(stateInfo.latitude) + ",";
  json += "\"longitude\":" + String(stateInfo.longitude) + ",";
  json += "\"temperature\":" + String(stateInfo.temperature) + ",";
  json += "\"pressure\":" + String(stateInfo.pressure) + ",";
  json += "\"humidity\":" + String(stateInfo.humidity) + ",";
  json += "\"altitude\":" + String(stateInfo.altitude);
  json += "}";
}
