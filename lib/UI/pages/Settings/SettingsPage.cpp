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

#include "SettingsPage.hpp"
#include "../../i18n.hpp"
#include "../../navigation/NFC/NFCNavigation.hpp"
#include "../../navigation/Settings/SettingsNavigation.hpp"
#include "gui.hpp"
#include "../../../../include/device_info.h"
#include "battery_monitor.hpp"
#include "DeepSleep.hpp"

extern String fw_md5; // From main.cpp

SettingsPage::~SettingsPage() {
  delete version;
  delete chip;
  delete board_widget;
  delete heap_usage;
  delete battery;
  if(sd_card_installed()) {
    delete sd_card;
    delete sd_card_size;
  }
  delete nfc_version;
  delete subghz;
#if defined(WAKEUP_PIN)
  delete deep_sleep;
#endif
  delete reboot;
  delete go_back;
}

void SettingsPage::display(String subghz_rev) {
  bool _sd_card_installed = sd_card_installed();

  grid = new Grid(screen, _sd_card_installed ? 12 : 9, 1);
  grid->set_y_spacing(10);

  version = new Text(screen, ST77XX_WHITE, (String)"Version: " + VERSION + " " + fw_md5.substring(0, 6));
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
  board_widget = new Text(screen, ST77XX_WHITE, board);
  heap_usage = new Text(screen, ST77XX_WHITE, "Heap: " +(String)((ESP.getHeapSize() - ESP.getFreeHeap()) / (1024)) + "/" + (ESP.getHeapSize() / (1024)) + "KB");
  chip = new Text(screen, ST77XX_WHITE, (String)"Chip: " + DEVICE + " " + ESP.getChipRevision() + " " + ESP.getCpuFreqMHz() + " MHz");
  battery = new Text(screen, ST77XX_WHITE, (String)"Battery: " + read_battery_level() + "%");

  if(_sd_card_installed) {
    sd_card = new Text(screen, ST77XX_WHITE, "SD Card type: " + get_current_sd_type());
    sd_card_size = new Text(screen, ST77XX_WHITE, (String)"SD Card usage: " + (float)SD.usedBytes() / (1024 * 1024 * 1024) + "/" + SD.cardSize() / (1024 * 1024 * 1024) + "GB");
  }

  nfc_version = new Text(screen, ST77XX_WHITE, "PN532 version: " + get_current_pn532_version());

  #ifdef CC1101_SUBGHZ
  String subghz_module = "CC1101";
  #else
  String subghz_module = "SX1276";
  #endif
  subghz = new Text(screen, ST77XX_WHITE, "SubGHZ module: " + subghz_module + " 0x" + subghz_rev);
  psram = new Text(screen, ST77XX_WHITE, (String)"PSRAM: " + (psramFound() ? (String)((float)(ESP.getPsramSize() - ESP.getFreePsram()) / (1024*1024)) + "/" + ((float)ESP.getPsramSize()/ (1024*1024)) + "MB": "Not installed"));
#if defined(WAKEUP_PIN)
  deep_sleep = new List(screen, "Deep Sleep", 2, ST77XX_WHITE, 20, ST77XX_BLACK, go_deep_sleep);
#endif
  reboot = new List(screen, "Reboot", 2, ST77XX_WHITE, 20, ST77XX_BLACK, [] () { ESP.restart(); });
  go_back = new List(screen, "Go back", 2, ST77XX_WHITE, 20, ST77XX_BLACK, goto_back_to_home);

  grid->add(version);
  grid->add(chip);
  grid->add(board_widget);
  grid->add(heap_usage);
  grid->add(battery);

  if(_sd_card_installed) {
    grid->add(sd_card);
    grid->add(sd_card_size);
  }

  grid->add(nfc_version);
  grid->add(subghz);
  grid->add(psram);

#if defined(WAKEUP_PIN)
  grid->add(deep_sleep);
#endif
  grid->add(reboot);
  grid->add(go_back);
  size_t lower_limit = _sd_card_installed ? 5 : 3;
  #if !defined(WAKEUP_PIN)
  lower_limit--;
  #endif
  grid->set_selected(lower_limit, true);
  grid->display();
}