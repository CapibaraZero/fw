/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2024 Andrea Canale.
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

#ifndef PERIPHERALS_ESP32_S3_DEVKITC_H
#define PERIPHERALS_ESP32_S3_DEVKITC_H
#ifdef ESP32S3_DEVKITC_BOARD
#include "../../../../include/pins.h"
#include "../../Peripherals.hpp"

class Peripherals_ESP32S3_DevKitC : public Peripherals {
 public:
  Peripherals_ESP32S3_DevKitC(/* args */) {};
  ~Peripherals_ESP32S3_DevKitC() {};
  void init_i2c_bus() {};
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