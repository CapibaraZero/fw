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
#include "GFXForms.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "Text.hpp"

#ifndef BLE_SPAM_PAGE_H
#define BLE_SPAM_PAGE_H

class BLESpamPage : public Page {
 private:
  Text *text;
  List *save;
  Grid *details_grid;

 public:
  BLESpamPage(GFXForms *_screen);
  ~BLESpamPage();
  void display() { details_grid->display(); }
  void up() {};
  void down() {};
  void left() {};
  void right() {};
};

#endif
