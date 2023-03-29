#include "Serializer.h"

void Serializer::printStateInfoToBothSerials(struct StateInfo& stateInfo, SoftwareSerial& espSerial) {
  Serial.print("\n");
  espSerial.print("\n");
  String json = "";
  json = "{";
  json += "\"packetNumber\":" + String(stateInfo.packetNumber) + ",";
  json += "\"latitude\":" + String(stateInfo.latitude) + ",";
  json += "\"longitude\":" + String(stateInfo.longitude) + ",";
  Serial.print(json);
  espSerial.print(json);
  json = "";
  json += "\"temperature\":" + String(stateInfo.temperature) + ",";
  json += "\"pressure\":" + String(stateInfo.pressure) + ",";
  json += "\"altitudeStatus\":" + String(stateInfo.altitudeStatus) + ",";
  json += "\"altitude\":" + String(stateInfo.altitude);
  json += "}";
  Serial.print(json);
  espSerial.print(json);
  Serial.print("\n");
  espSerial.print("\n");
}
