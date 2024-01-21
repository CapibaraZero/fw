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

#include "GFXForms.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "../Page.hpp"

#ifndef WIFI_SCAN_SAVE_RESULTS_PAGE_H
#define WIFI_SCAN_SAVE_RESULTS_PAGE_H

class WifiScanSaveResultPage : public Page {
 private:
  Grid *selection;
  int selection_index = 0;
  List *save_sd;
  List *sniff_filter;
  List *go_back;
  List *exit_btn;

 public:
  WifiScanSaveResultPage(GFXForms *_screen);
  ~WifiScanSaveResultPage();

  void up();
  void down();
  void left(){};
  void right(){};
  void display();
  int get_index() { return selection_index; }
};

#endif