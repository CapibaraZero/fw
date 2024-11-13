#include "GFXForms.hpp"  // Fix building errors
#include "gui.hpp"
#include "nfc_attacks.hpp"
#include "wifi_attack.hpp"

typedef struct {
  NFCAttacks *attacks;
  Gui *gui;
  char *path;
} NFCTasksParams;