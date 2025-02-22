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

#include "../../navigation/NFC/NFCNavigation.hpp"
#include "../Page.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "Text.hpp"

#ifndef NFC_POLLING_WAITING_PAGE_H
#define NFC_POLLING_WAITING_PAGE_H

class NFCPollingWaitingPage : public Page {
 private:
  Text *polling_in_progress;
  Text *info_msg;
  List *go_back;

 public:
  NFCPollingWaitingPage(uint8_t _position_limit, uint8_t _lower_limit,
                        uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~NFCPollingWaitingPage();
  void display();

  void set_selected(int pos, bool status) { grid->set_selected(pos, status); };
  void click() { grid->click(1, stop_nfc_polling); }
};

#endif
