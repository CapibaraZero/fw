#ifndef PERIPHERALS_ESP32_S3_DEVKITC_H
#define PERIPHERALS_ESP32_S3_DEVKITC_H
#ifdef ESP32S3_DEVKITC_BOARD
#include "../../../../include/pins.h"
#include "../../Peripherals.hpp"

class Peripherals_ESP32S3_DevKitC : public Peripherals {
 public:
  Peripherals_ESP32S3_DevKitC(/* args */) {};
  ~Peripherals_ESP32S3_DevKitC() {};
  void init_nfc_bus() {};
  void init_sd() {
    common_init_sd(SD_CARD_SCK, SD_CARD_MISO, SD_CARD_MOSI, SD_CARD_CS);
  };
  void init_navigation() {
    common_init_navigation(UP_BTN_PIN, DOWN_BTN_PIN, LEFT_BTN_PIN,
                           RIGHT_BTN_PIN, OK_BTN_PIN);
  };
};

#endif
#endif