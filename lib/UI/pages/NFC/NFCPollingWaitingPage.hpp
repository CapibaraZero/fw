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
#include "List.hpp"
#include "../Page.hpp"

#ifndef NFC_POLLING_WAITING_PAGE_H
#define NFC_POLLING_WAITING_PAGE_H

class NFCPollingWaitingPage : public Page {
 private:
  Text *polling_in_progress;
  Text *info_msg;
  List *go_back;
  Grid *nfc_grid;

 public:
  NFCPollingWaitingPage(GFXForms *_screen);
  ~NFCPollingWaitingPage();
  void display();
  void up(){};
  void down(){};
  void left(){};
  void right(){};
  void set_selected(int pos, bool status) {
    nfc_grid->set_selected(pos, status);
  };
};

#endif
