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

#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "../../include/pins.h"
#include "../Page.hpp"
#include "Grid.hpp"
#include "Text.hpp"
#include "widgets/RectText.hpp"

class MainPage : public Page {
 private:
  RectText *wifi = nullptr;
  RectText *ble = nullptr;
  RectText *badusb = nullptr;
  RectText *SubGhz = nullptr;
  RectText *NFC = nullptr;
  RectText *IR = nullptr;
  RectText *scripts = nullptr;
  RectText *settings = nullptr;
  Text *text = nullptr;
#if DISPLAY_WIDTH == 170 && DISPLAY_HEIGHT == 320
  Text *btn_level = nullptr;
#endif
  int read_bat_level();
  // Text *battery_level;
 public:
  MainPage(uint8_t _position_limit, uint8_t _lower_limit,
           uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~MainPage();
  void display();
  void left();
  void right();
  void set_battery_level() {
    int level = read_bat_level();
#if DISPLAY_WIDTH != 170
    Text battery_level =
        Text(screen, 0xFFFF, "Battery:" + (String)level + "%", 2U, true);
    battery_level.set_pos(5, 220);
    battery_level.display();
#else
    btn_level->set_text((String)level + "%");
#endif
  };
};

#endif