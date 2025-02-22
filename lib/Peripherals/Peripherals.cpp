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

#include "Peripherals.hpp"

#include "Arduino.h"
#include "SPI.h"
#include "navigation/buttons/btn_routines.hpp"
#include "navigation/navigation.hpp"
#include "posixsd.hpp"

uint32_t sd_sum_Mbyte;
uint32_t sd_used_Mbyte;

SPIClass SD_CARD_SPI(HSPI);

bool Peripherals::common_init_sd(size_t sck, size_t miso, size_t mosi,
                                 size_t cs) {
  SD_CARD_SPI.end();
  SD_CARD_SPI.begin(sck, miso, mosi);
  bool status = SD.begin(SD_CARD_CS, SD_CARD_SPI);
  if (!status) {
    Serial.println("init_sdcard failed");
  };
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return false;
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

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  sd_sum_Mbyte = (SD.totalBytes() / (1024 * 1024));
  sd_used_Mbyte = (SD.usedBytes() / (1024 * 1024));

  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %dMB\n", sd_sum_Mbyte);
  Serial.printf("Used space: %dMB\n", sd_used_Mbyte);

  return status;
}

void Peripherals::init_navigation_btn(int pin, void callback(), int input_mode,
                                      int isr_mode) {
  pinMode(pin, input_mode);
  attachInterrupt(pin, callback, isr_mode);
}

void Peripherals::common_init_navigation(EasyButton *up, EasyButton *down, EasyButton *left, EasyButton *right) {
#ifdef BTN_NAVIGATION
  up->begin();
  up->onPressed(handle_up_button);
  down->begin();
  down->onPressed(handle_down_button);
  left->begin();
  left->onPressed(handle_left_button);
  right->begin();
  right->onPressed(handle_right_button);
#endif
}