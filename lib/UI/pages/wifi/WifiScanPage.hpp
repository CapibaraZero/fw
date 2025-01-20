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

#include "../Page.hpp"
#include "Grid.hpp"
#include "Text.hpp"

#ifndef WIFISCANPAGE_H
#define WIFISCANPAGE_H

class WifiScanPage : public Page {
 private:
  Text *wifi_scan_text;
  Text *wifi_scan_progress;
  Text *wifi_scan_current_ch;

 public:
  WifiScanPage(uint8_t _position_limit, uint8_t _lower_limit,
               uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~WifiScanPage();
  void display();
  void update_progress(char *_progress) {
    wifi_scan_progress->set_text(_progress);
  };
  void set_ch_text(char *channel) { wifi_scan_current_ch->set_text(channel); };
  // Up and down are not necessary here so overload with methods that do nothing
  void up() {};
  void down() {};
  void click() {};
};

#endif