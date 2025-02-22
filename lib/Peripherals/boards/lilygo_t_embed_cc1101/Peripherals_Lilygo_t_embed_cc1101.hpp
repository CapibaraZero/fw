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
 *
 * I2C initialization from:
 * https://github.com/Xinyuan-LilyGO/T-Embed-CC1101/blob/master/examples/pn532_test/pn532_test.ino
 * And:
 * https://github.com/Xinyuan-LilyGO/T-Embed-CC1101/blob/master/examples/factory_test/factory_test.ino
 */

#ifndef PERIPHERALS_LILYGO_T_EMBED_CC1101_H
#define PERIPHERALS_LILYGO_T_EMBED_CC1101_H

#include "../../../../include/pins.h"
#include "../../Peripherals.hpp"
#include "Arduino.h"
#include "Wire.h"
#include "navigation/buttons/btn_routines.hpp"
#include "navigation/navigation.hpp"

class Peripherals_Lilygo_t_embed_cc1101 : public Peripherals {
 private:
  /* data */
 public:
  Peripherals_Lilygo_t_embed_cc1101(/* args */) {};
  ~Peripherals_Lilygo_t_embed_cc1101() {};
  void init_i2c_bus() {
    // iic scan
    byte error, address;
    int nDevices = 0;
    Serial.println("Scanning for I2C devices ...");
    Wire.begin(NFC_BUS_SDA, NFC_BUS_SCL);
    for (address = 0x01; address < 0x7F; address++) {
      Wire.beginTransmission(address);
      // 0: success.
      // 1: data too long to fit in transmit buffer.
      // 2: received NACK on transmit of address.
      // 3: received NACK on transmit of data.
      // 4: other error.
      // 5: timeout
      error = Wire.endTransmission();
      if (error == 0) {  // 0: success.
        nDevices++;
        Serial.printf("I2C device found at address 0x%x\n", address);
      } else if (error != 2) {
        Serial.printf("Error %d at address 0x%02X\n", error, address);
      }
    }
    if (nDevices == 0) {
      Serial.println("No I2C devices found");
    }

    pinMode(IR_EMITTER_PIN, OUTPUT);
    digitalWrite(IR_EMITTER_PIN, HIGH);  // Power on IR

    pinMode(BOARD_PWR_EN, OUTPUT);
    digitalWrite(BOARD_PWR_EN, HIGH);  // Power on CC1101 an

    // NFC
    pinMode(PN532_RST, OUTPUT);
    digitalWrite(PN532_RST, HIGH);
    pinMode(PN532_IRQ, OPEN_DRAIN);
  };
  void init_sd() {
    common_init_sd(SD_CARD_SCK, SD_CARD_MISO, SD_CARD_MOSI, SD_CARD_CS);
  };
  void init_navigation() {
    init_rotary_encoder();
    init_ok_btn();
  };
  void loop_code() {
    handle_encoder();
    ok_btn.read();
  }
};

#endif