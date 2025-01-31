/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2025 Andrea Canale.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PERIPHERALS_AirM2M_CORE_ESP32C3_H
#define PERIPHERALS_AirM2M_CORE_ESP32C3_H
#ifdef ARDUINO_AirM2M_CORE_ESP32C3
#include "../../../../include/pins.h"
#include "../../Peripherals.hpp"
#include "SD.h"

class Peripherals_AirM2M_CORE_ESP32C3 : public Peripherals {
private:
  EasyButton up_btn = EasyButton(UP_BTN_PIN);
  EasyButton down_btn = EasyButton(DOWN_BTN_PIN);
  EasyButton left_btn = EasyButton(LEFT_BTN_PIN);
  EasyButton right_btn = EasyButton(RIGHT_BTN_PIN);
public:
  Peripherals_AirM2M_CORE_ESP32C3(/* args */) {};
  ~Peripherals_AirM2M_CORE_ESP32C3() {};
  void init_i2c_bus() {};
  void init_sd() {
    bool status = SD.begin(SD_CARD_CS);
    if (!status) {
      Serial.println("init_sdcard failed");
    };
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE) {
      Serial.println("No SD card attached");
      // return false;
    }

    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC) {
      Serial.println("MMC");
    } else if (cardType == CARD_SD) {
      Serial.println("SDSC");
    } else if (cardType == CARD_SDHC) {
      Serial.println("SDHC");
    } else {
      Serial.println("UNKNOWN");
    }
    uint32_t sd_sum_Mbyte;
    uint32_t sd_used_Mbyte;
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    sd_sum_Mbyte = (SD.totalBytes() / (1024 * 1024));
    sd_used_Mbyte = (SD.usedBytes() / (1024 * 1024));

    Serial.printf("SD Card Size: %lluMB\n", cardSize);
    Serial.printf("Total space: %dMB\n", sd_sum_Mbyte);
    Serial.printf("Used space: %dMB\n", sd_used_Mbyte);

    // return status;
    // common_init_sd(SD_CARD_SCK, SD_CARD_MISO, SD_CARD_MOSI, SD_CARD_CS);
  };
  void init_navigation() {
    common_init_navigation(&up_btn, &down_btn, &left_btn,
                           &right_btn);
    init_ok_btn();
  };
  void loop_code() {
    up_btn.read();
    down_btn.read();
    left_btn.read();
    right_btn.read();
    ok_btn.read();
  }
};

#endif
#endif