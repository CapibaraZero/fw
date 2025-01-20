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

#ifndef BLESCANPAGE_H
#define BLESCANPAGE_H

class BLEScanPage : public Page {
 private:
  Text *ble_scan_text;
  Text *ble_scan_progress;
  Text *ble_scan_adv_devices;

 public:
  BLEScanPage(uint8_t _position_limit, uint8_t _lower_limit,
              uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~BLEScanPage();
  void display();
  void update_progress(char *_progress) {
    ble_scan_progress->set_text(_progress);
  };
  void set_adv_devices_text(const char *channel) {
    ble_scan_adv_devices->set_text(channel);
  }
};

#endif
