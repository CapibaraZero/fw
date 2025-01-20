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

#include "../../i18n.hpp"
#include "../../i18n/NFC/nfc_dump_iso14443a_keys.h"
#include "../Page.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "Text.hpp"

#ifndef NFC_DUMP_RESULT_PAGE_H
#define NFC_DUMP_RESULT_PAGE_H

class NFCDumpResultPage : public Page {
 private:
  Text *dumping_to_sd;
  Text *dumped_sectors;
  Text *unreadable_sectors;
  Text *unauthenticated_sectors;
  List *save_to_sd;
  List *return_back;
  List *exit_page;

 public:
  NFCDumpResultPage(uint8_t _position_limit, uint8_t _lower_limit,
                    uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~NFCDumpResultPage();
  void display();

  void click(int pos, void callback()) { grid->click(pos, callback); };
  void set_selected(int pos, bool status) { grid->set_selected(pos, status); };
  void set_dumped(int dumped) {
    dumped_sectors->set_text(english_words->at(NFC_DUMPED_SECTORS_KEY) +
                             (String)dumped);
  }
  void set_unreadable(int unreadable) {
    unreadable_sectors->set_text(english_words->at(NFC_UNREADABLE_SECTORS_KEY) +
                                 (String)unreadable);
  }
  void set_unauthenticated(int unauthenticated) {
    unauthenticated_sectors->set_text(
        english_words->at(NFC_UNAUTHENTICATED_SECTORS_KEY) +
        (String)unauthenticated);
  }
};

#endif
