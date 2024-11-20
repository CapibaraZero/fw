#include "Peripherals.hpp"

#include "Arduino.h"
#include "SPI.h"
#include "posixsd.hpp"
#include "navigation/buttons/btn_routines.hpp"
#include "navigation/navigation.hpp"

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

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return false;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
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

void Peripherals::init_navigation_btn(int pin, void callback(), int input_mode, int isr_mode) {
  pinMode(pin, input_mode);
  attachInterrupt(pin, callback, isr_mode);
}

void Peripherals::common_init_navigation(size_t up, size_t down, size_t left,
                                         size_t right, size_t ok) {
#if BTN_NAVIGATION
  init_navigation_btn(up, handle_up_button);
  init_navigation_btn(down, handle_down_button);
  init_navigation_btn(left, handle_left_button);
  init_navigation_btn(right, handle_right_button);
  init_navigation_btn(ok, handle_ok_button);
#endif
}