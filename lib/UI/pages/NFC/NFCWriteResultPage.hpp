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
#include "Text.hpp"

#ifndef NFC_WRITE_RESULT_PAGE_H
#define NFC_WRITE_RESULT_PAGE_H

class NFCWriteResultPage : public Page {
 private:
  Text *write_info;
  Text *wrote_sectors;
  Text *unwritable_sectors;
  List *return_back;
  List *exit_page;

 public:
  NFCWriteResultPage(uint8_t _position_limit, uint8_t _lower_limit,
                     uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~NFCWriteResultPage();
  void display();
  void click() {};
  void click(int pos, void callback()) {};
  void set_selected(int pos, bool status) { grid->set_selected(pos, status); };
  void set_wrote_sectors(int sectors) {
    wrote_sectors->set_text("Wrote sectors: " + (String)sectors);
  }
  void set_unwritable_sectors(int unwritable) {
    unwritable_sectors->set_text("Unwritable sectors: " + (String)unwritable);
  }
};

#endif
