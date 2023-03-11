#ifndef TPA_STRUCTURE
#define TPA_STRUCTURE

struct __attribute__((packed)) TPAState {
  float pressure;
  float temperature;
  float humidity;
  float altitude;
};


#endif