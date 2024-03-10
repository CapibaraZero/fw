#include <stdint.h>

#include "wifi_attack.hpp"

typedef struct {
  uint8_t *bssid;
  int ch;
  WifiAttack *attack;
} BSSIDSniff;