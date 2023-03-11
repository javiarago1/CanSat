#ifndef INFO_STRUCTURE
#define INFO_STRUCTURE



struct __attribute__((packed)) StateInfo {
  float packetNumber;
  float latitude;
  float longitude;
  float temperature;
  float pressure;
  float humidity;
  float altitude;
};

#endif