/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2025 Andrea Canale.
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

#include "../../../../include/debug.h"
#include "../Page.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "Text.hpp"

#ifndef NFC_POLLING_RESULT_PAGE_H
#define NFC_POLLING_RESULT_PAGE_H

class NFCPollingResultPage : public Page {
 private:
  Text *tag_info;
  Text *uid_text;
  List *dump_to_sd;
  List *write_tag;
  List *format_tag;
  List *bruteforce_tag;
  List *emulate_tag;
  List *exit_page;

 public:
  NFCPollingResultPage(uint8_t _position_limit, uint8_t _lower_limit,
                       uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~NFCPollingResultPage();
  /// @brief Mock display
  /// @deprecated
  void display() {
    LOG_ERROR("NFCPollingResultPage::display() Not implemented");
  };
  void display(uint8_t *uid, uint8_t length, const char *tag_name);

  void set_selected(int pos, bool status) { grid->set_selected(pos, status); };
  void click(int pos, void callback()) { grid->click(pos, callback); };
};

#endif
