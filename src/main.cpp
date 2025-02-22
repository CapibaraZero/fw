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

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7735
#include <Arduino.h>

#include <GFXForms.hpp>

#include "DeepSleep.hpp"
#include "Peripherals.hpp"
#include "SPI.h"
#include "battery_monitor.hpp"
#include "ble_hid/BLEHid.hpp"  // Without this build fails
#include "debug.h"
#include "freertos/task.h"
#include "gui.hpp"
#include "i18n.hpp"
#include "navigation/navigation.hpp"
#include "pins.h"
#include "posixsd.hpp"
#include "style.h"

/* TODO: To lower this, we can may switch to heap for wifi_networks */
#define TASK_STACK_SIZE 16000

Gui *main_gui;
Adafruit_ST7789 *display;
GFXForms *screen;
SPIClass display_spi;
String fw_md5 = ESP.getSketchMD5(); // Calculate MD5 at startup(save time when loading settings)

#ifdef ARDUINO_NANO_ESP32
Peripherals_Arduino_Nano_ESP32 peripherals = Peripherals_Arduino_Nano_ESP32();
#elif ESP32S3_DEVKITC_BOARD
Peripherals_ESP32S3_DevKitC peripherals = Peripherals_ESP32S3_DevKitC();
#elif LILYGO_T_EMBED_CC1101
Peripherals_Lilygo_t_embed_cc1101 peripherals =
    Peripherals_Lilygo_t_embed_cc1101();
#endif

void setup() {
  SERIAL_DEVICE.begin(115200);
  delay(2000);

  peripherals.init_i2c_bus();

  #ifdef BOARD_HAS_PSRAM
    if(psramInit()) {
      LOG_INFO("PSRAM initialized\n");
    }
    heap_caps_malloc_extmem_enable(4096); // Malloc larger than 4KB will be placed in PSRAM
  #endif
  init_english_dict();

#ifdef BATTERY_MONITOR
  pinMode(BATTERY_MONITOR, INPUT);
#endif

  display_spi.begin(TFT_SCLK, TFT_MISO, TFT_MOSI, TFT_CS);

  display = new Adafruit_ST7789(&display_spi, TFT_CS, TFT_DC, -1);
  screen = new GFXForms(DISPLAY_WIDTH, DISPLAY_HEIGHT, display);

  screen->set_rotation(1);
  screen->set_background_color(HOME_BACKGROUND_COLOR);
  main_gui = new Gui(screen);
  main_gui->init_gui();

  peripherals.init_navigation();

  xTaskCreate(&set_selected_listener, "set_selected_listener", 8192,
              (void *)main_gui, 1, NULL);
#if defined(STANDBY_BTN) && defined(WAKEUP_PIN)
  enable_deep_sleep();
#endif
  display_spi.setHwCs(1);
#ifdef TFT_BLK
  analogWrite(TFT_BLK, 255);
#endif
  peripherals.init_sd();
}

void loop() {
  peripherals.loop_code();
}
