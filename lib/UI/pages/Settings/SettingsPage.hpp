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

#include "../Page.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "SD.h"

#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

class SettingsPage : public Page {
 private:
  Text *version;
  Text *chip;
  Text *board_widget;
  Text *heap_usage;
  Text *battery;
  Text *sd_card;
  Text *sd_card_size;
  Text *nfc_version;
  Text *subghz;
  Text *psram;
  List *deep_sleep;
  List *reboot;
  List *go_back;
  List *empty;

  bool sd_card_installed() {
    return SD.cardType() != CARD_NONE;
  }

  String get_current_sd_type() {
    uint8_t cardType = SD.cardType();
    switch (cardType) {
    case CARD_NONE:
      return "None";
      break;
    case CARD_MMC:
      return "MMC";
      break;
    case CARD_SD:
      return "SDSC";
      break;
    case CARD_SDHC:
      return "SDHC";
      break;
    default:
      return "Unknown";
      break;
    }
  }
 public:
  SettingsPage(uint8_t _position_limit, uint8_t _lower_limit,
                              uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~SettingsPage();
  void display() {};
  void display(String subghz_rev);
  void click(int pos, void callback()) { 
      grid->click(pos, callback); 
  };
  void set_selected(int pos, bool status) { 
      grid->set_pos(pos, status);
  };
};

#endif