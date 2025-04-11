#include "SubGHZ.hpp"
#include "config_struct.h"
#include "network_attacks.hpp"
#include "wifi_attack.hpp"

typedef struct SubGHZTaskParameters {
  SubGHZ *subghz;
  
  float rssi_threshold;
} SubGHZTaskParameters;