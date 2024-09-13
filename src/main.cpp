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

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7735
#include <Arduino.h>
#include <LittleFS.h>

#include <GFXForms.hpp>

#include "SPI.h"
#include "battery_monitor.hpp"
#include "ble_hid/BLEHid.hpp"  // Without this build fails
#include "debug.h"
#include "display_config.h"
#include "freertos/task.h"
#include "gui.hpp"
#include "i18n.hpp"
#include "navigation/buttons/btn_routines.hpp"
#include "navigation/navigation.hpp"
#include "pins.h"
#include "posixsd.hpp"
#include "style.h"

/* TODO: To lower this, we can may switch to heap for wifi_networks */
#define TASK_STACK_SIZE 16000

static bool init_sd() {
  SPI.begin(SD_CARD_SCK, SD_CARD_MISO, SD_CARD_MOSI, SD_CARD_CS);
  bool status = init_sdcard(SD_CARD_CS);
  if (!status) {
    LOG_ERROR("init_sdcard failed");
  };
  return status;
}

void init_navigation_btn(int pin, void callback()) {
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(pin, callback, FALLING);
}

Gui *main_gui;
Adafruit_ST7789 *display;
GFXForms *screen;

// Check if a SubGHZ record needs to be saved in SD(Arduino Nano ESP32)
static void merge_littlefs_to_sd(void *pv) {
  if (LittleFS.exists("/littlefs/tmp.json")) {
    LOG_INFO("tmp.json exists, copying to SD\n");
    File file = LittleFS.open("/littlefs/tmp.json");
    File to_copy = SD.open("/subghz/" + (String)millis() + ".json", "w", true);
    vector<uint8_t> text;
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

static bool init_littlefs() {
  bool status = LittleFS.begin(true);
  if (!status) {
    LOG_ERROR("LittleFS Mount Failed");
  }
  return status;
}

void setup() {
#ifdef ARDUINO_NANO_ESP32
  Serial.begin(115200);
  Serial.println("Test");
  delay(2000);
  if (init_sd() && init_littlefs()) {
    xTaskCreate(merge_littlefs_to_sd, "merge_littlefs_to_sd", 4000, NULL, 5,
                NULL);
  }
#else
  Serial0.begin(115200);
  init_sd();
#endif
  init_english_dict();
  pinMode(BATTERY_MONITOR, INPUT);
  display = new Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
  screen = new GFXForms(DISPLAY_WIDTH, DISPLAY_HEIGHT, display);
  screen->set_rotation(1);
  screen->set_background_color(HOME_BACKGROUND_COLOR);
  main_gui = new Gui(screen);
  main_gui->init_gui();
  init_navigation_btn(UP_BTN_PIN, handle_up_button);
  init_navigation_btn(DOWN_BTN_PIN, handle_down_button);
  init_navigation_btn(RIGHT_BTN_PIN, handle_right_button);
  init_navigation_btn(LEFT_BTN_PIN, handle_left_button);
  init_navigation_btn(OK_BTN_PIN, handle_ok_button);

  xTaskCreate(&set_selected_listener, "set_selected_listener", 8192,
              (void *)main_gui, 1, NULL);
}

void loop() {
  LOG_INFO("Loop\n");  // Avoid FreeRTOS watchdog trigger
  delay(1000);
}
