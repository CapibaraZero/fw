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

#include "ui.h"
#include "vars.h"
#include <Arduino.h>
#include "../../include/device_info.h"
#include "SD.h"
#include "sd_utils.h"
#include "nfc_actions.hpp"
#include "subghz_actions.hpp"
#include "DeepSleep.hpp"

extern String fw_md5; // From main.cpp

void create_sd_widgets() {
  set_var_sd_card_installed(!sd_card_installed());

  set_var_sd_card_type(("SD Card type: " + get_current_sd_type()).c_str());

  set_var_sd_card_usage(((String) "SD Card usage: " + (float)SD.usedBytes() / (1024 * 1024 * 1024) + "/" + SD.cardSize() / (1024 * 1024 * 1024) + "GB").c_str());
}

void create_heap_widgets() {
  uint32_t heap_usage = (ESP.getHeapSize() - ESP.getFreeHeap());
  set_var_heap_usage(("Heap usage: " +(String)(heap_usage / (1024)) + "/" + (ESP.getHeapSize() / (1024)) + "KB").c_str());
}

void create_subghz_widgets() {
  #ifdef CC1101_SUBGHZ
  String subghz_module = "CC1101";
#else
  String subghz_module = "SX1276";
#endif
  char *subghz_rev = get_subghz_chip_revision();
  set_var_subghz_revision(((String)"SubGHZ module: " + subghz_module + " 0x" + subghz_rev).c_str());
  free(subghz_rev);
}

void create_psram_widgets() {
  // Init psram
  set_var_psram_installed(!psramFound());
  float used_psram = (float)(ESP.getPsramSize() - ESP.getFreePsram());
  set_var_psram_size(((String) "PSRAM usage: " + (used_psram / (1024*1024)) + "/" + ((float)ESP.getPsramSize()/ (1024*1024)) + "MB").c_str());  
}

void create_board_widget() {
  String board = "";
#ifdef ESP32S3_DEVKITC_BOARD
  board = "ESP32-S3 DevKitC";
#elif ARDUINO_NANO_ESP32
  board = "Arduino Nano ESP32";
#elif LILYGO_T_EMBED_CC1101
  board = "LilyGo T-Embed CC1101";
#else
  board = "Unknown";
#endif
  set_var_board(("Board: " + board).c_str());
}

extern "C" void action_go_to_settings(lv_event_t *e) {

  set_var_sw_version(((String)"Version: " + VERSION + " " + fw_md5.substring(0, 6)).c_str());

  create_board_widget();
  create_sd_widgets();
  create_heap_widgets();

  set_var_chip_revision(((String) "Chip: " + DEVICE + " " + ESP.getChipRevision() + " " + ESP.getCpuFreqMHz() + " MHz").c_str());

  create_subghz_widgets();
  set_var_nfc_revision(((String)"PN532 revision: " + get_current_pn532_version()).c_str());

  create_psram_widgets();
  create_screen_settings_page();
  loadScreen(SCREEN_ID_SETTINGS_PAGE);
}

extern "C" void action_esp_deep_sleep(lv_event_t *e) {
  go_deep_sleep();
}

extern "C" void action_esp_reboot(lv_event_t *e) {
  ESP.restart();
}