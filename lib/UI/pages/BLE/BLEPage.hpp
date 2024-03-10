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
#include "List.hpp"

#ifndef BLE_PAGE_H
#define BLE_PAGE_H

class BLEPage : public Page {
 private:
  //  List *ble_list;
  List *ble_sniff;
  List *apple_juice;
  List *samsung_ble;
  List *swift_pair;
  Grid *ble_grid;

 public:
  BLEPage(GFXForms *_screen);
  ~BLEPage();
  void display();
  void click(int pos, void callback()) { ble_grid->click(pos, callback); };
  void set_selected(int pos, bool status) {
    ble_grid->set_selected(pos, status);
  };
  void up() {};
  void down() {};
  void left() {};
  void right() {};
};

#endif
