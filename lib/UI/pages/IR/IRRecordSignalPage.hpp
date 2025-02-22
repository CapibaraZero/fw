
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

#ifndef IR_RECORD_SIGNAL_PAGE_H
#define IR_RECORD_SIGNAL_PAGE_H

class IRRecordSignalPage : public Page {
 private:
  Text *protocol = nullptr;
  Text *addr;
  Text *cmd;
  Text *len;
  List *save;
  List *retry;
  List *stop;

 public:
  IRRecordSignalPage(uint8_t _position_limit, uint8_t _lower_limit,
                     uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~IRRecordSignalPage();
  void display();

  void set_selected(int pos, bool status) { grid->set_selected(pos, status); };
  void click(int pos, void callback()) { grid->click(pos, callback); };
  void set_signal(String _protocol, uint16_t _addr, uint16_t _cmd,
                  uint32_t len);
};

#endif
