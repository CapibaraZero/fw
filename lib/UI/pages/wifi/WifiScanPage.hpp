/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or https://capibarazero.github.io/).
 * Copyright (c) 2024 Andrea Canale.
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

#include "Grid.hpp"
#include "Text.hpp"
#include "../Page.hpp"

#ifndef WIFISCANPAGE_H
#define WIFISCANPAGE_H

class WifiScanPage: public Page {
 private:
  Grid *wifi_scan_grid;
  Text *wifi_scan_text;
  Text *wifi_scan_progress;
  Text *wifi_scan_current_ch;
 public:
  WifiScanPage(GFXForms *_screen);
  ~WifiScanPage();
  void display();
  void update_progress(char *_progress){
    wifi_scan_progress->set_text(_progress);
  };
  void set_ch_text(char *channel) {
    wifi_scan_current_ch->set_text(channel);
  }
    void up(){};
  void down(){};
  void left(){};
  void right(){};
};

#endif