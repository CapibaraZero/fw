#ifndef SUBGHZ_CONFIG_STRUCT_H
#define SUBGHZ_CONFIG_STRUCT_H

#include "SubGHZ.hpp"

typedef struct SubGHZRAWRecorderConfig {
  float freq;
  float bw;
  float deviation;
  int modulation;
  float rssi_threshold;
} SubGHZRAWRecorderConfig;

typedef struct {
  float freq;
  float bw;
  float deviation;
  int modulation;
  size_t len;
  uint8_t *data;
} SubGHZCapture;

#endif