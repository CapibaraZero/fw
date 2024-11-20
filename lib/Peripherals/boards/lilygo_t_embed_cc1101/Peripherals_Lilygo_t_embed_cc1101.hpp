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
  void init_nfc_bus() {
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
    digitalWrite(IR_EMITTER_PIN, HIGH); // Power on IR

    pinMode(BOARD_PWR_EN, OUTPUT);
    digitalWrite(BOARD_PWR_EN, HIGH);  // Power on CC1101 an
    
    // NFC
    pinMode(NFC_RST, OUTPUT);
    digitalWrite(NFC_RST, HIGH);
    pinMode(NFC_IRQ, OPEN_DRAIN);
  };
  void init_sd() {
    common_init_sd(SD_CARD_SCK, SD_CARD_MISO, SD_CARD_MOSI, SD_CARD_CS);
  };
  void init_navigation() {
    init_rotary_encoder();
    // Since rotary isn't really precise, tick just on Encoder A Pin interrupt
    //attachInterrupt(ENCODER_B_PIN, handle_encoder, CHANGE);
    attachInterrupt(ENCODER_A_PIN, handle_encoder, CHANGE);
    init_navigation_btn(OK_BTN_PIN, handle_ok_button, INPUT, HIGH);
  };
};

#endif