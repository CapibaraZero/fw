#include "nfc_attacks.hpp"
#include "GFXForms.hpp" // Fix building errors
#include "wifi_attack.hpp"
#include "gui.hpp"

typedef struct {
    NFCAttacks *attacks;
    Gui *gui;
} NFCTasksParams;