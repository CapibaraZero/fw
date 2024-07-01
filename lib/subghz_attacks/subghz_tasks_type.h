#include "SubGHZ.hpp"
#include "GFXForms.hpp"  // Fix building errors
#include "gui.hpp"
#include "network_attacks.hpp"
#include "wifi_attack.hpp"
#include "config_struct.h"

typedef struct SubGHZTaskParameters {
    SubGHZ *subghz;
    Gui *gui;
    float rssi_threshold;
}SubGHZTaskParameters;