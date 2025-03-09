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

#include <Arduino.h>

#include "gui.hpp"
#include "DeepSleep.hpp"
#include "Peripherals.hpp"
#include "SPI.h"
#include "battery_monitor.hpp"
#include "ble_hid/BLEHid.hpp"  // Without this build fails
#include "debug.h"
#include "freertos/task.h"
#include "pins.h"
#include "posixsd.hpp"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"
#include "ui.h"

/* TODO: To lower this, we can may switch to heap for wifi_networks */
#define TASK_STACK_SIZE 16000

Gui *main_gui;
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

#ifdef BATTERY_MONITOR
  pinMode(BATTERY_MONITOR, INPUT);
#endif
#if defined(STANDBY_BTN) && defined(WAKEUP_PIN)
  enable_deep_sleep();
#endif
  peripherals.init_sd();

  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();
  ui_init();
}

void loop() {
  lv_timer_handler();
  ui_tick();
}
