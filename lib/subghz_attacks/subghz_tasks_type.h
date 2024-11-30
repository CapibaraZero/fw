#include "GFXForms.hpp"  // Fix building errors
#include "SubGHZ.hpp"
#include "config_struct.h"
#include "gui.hpp"
#include "network_attacks.hpp"
#include "wifi_attack.hpp"

typedef struct SubGHZTaskParameters {
  SubGHZ *subghz;
  Gui *gui;
  float rssi_threshold;
} SubGHZTaskParameters;