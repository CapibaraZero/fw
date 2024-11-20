#ifndef PERIPHERALS_ARDUINO_NANO_ESP32_H
#define PERIPHERALS_ARDUINO_NANO_ESP32_H

#ifdef ARDUINO_NANO_ESP32
#include <LittleFS.h>

#include "../../../../include/debug.h"
#include "../../../../include/pins.h"
#include "../../Peripherals.hpp"
#include "posixsd.hpp"
#include "vector"

// Check if a SubGHZ record needs to be saved in SD(Arduino Nano ESP32)
static void merge_littlefs_to_sd(void *pv) {
  if (LittleFS.exists("/littlefs/tmp.json")) {
    LOG_INFO("tmp.json exists, copying to SD\n");
    File file = LittleFS.open("/littlefs/tmp.json");
    File to_copy = SD.open("/subghz/" + (String)millis() + ".json", "w", true);
    std::vector<uint8_t> text;
    uint8_t textseg;
    while (file.available()) {
      file.read(&textseg, 1);
      text.push_back(textseg);
    }
    if (!to_copy.write(text.data(), text.size())) {
      LOG_ERROR("Failed to write file in SD\n");
    } else {
      LOG_INFO("Write successfully to file\n");
    }
    file.close();
    to_copy.close();
    if (!LittleFS.remove("/littlefs/tmp.json")) {
      LOG_ERROR("Failed to remove file from LittleFS\n");
    };
  }
  vTaskDelete(NULL);
}

class Peripherals_Arduino_Nano_ESP32 : public Peripherals {
 private:
  bool init_littlefs() {
    bool status = LittleFS.begin(true);
    if (!status) {
      LOG_ERROR("LittleFS Mount Failed");
    }
    return status;
  };

 public:
  Peripherals_Arduino_Nano_ESP32(/* args */) {};
  ~Peripherals_Arduino_Nano_ESP32() {};
  void init_nfc_bus() {};
  void init_sd() {
    bool status = true;
    status = status && common_init_sd(SD_CARD_SCK, SD_CARD_MISO, SD_CARD_MOSI,
                                      SD_CARD_CS);
    status = status && init_littlefs();
    if (status) {
      xTaskCreate(merge_littlefs_to_sd, "merge_littlefs_to_sd", 4000, NULL, 5,
                  NULL);
    }
  };
  void init_navigation() {
    common_init_navigation(UP_BTN_PIN, DOWN_BTN_PIN, LEFT_BTN_PIN,
                           RIGHT_BTN_PIN, OK_BTN_PIN);
  };
};
#endif
#endif