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

#include "../../i18n.hpp"
#include "../../i18n/NFC/nfc_format_page_keys.h"
#include "../Page.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "Text.hpp"

#ifndef NFC_EMV_READ_PAGE_H
#define NFC_EMV_READ_PAGE_H

class NFCEMVReadPage : public Page {
 private:
  Text *card_type;
  Text *card_number;
  Text *issue_date;
  Text *expire;
  List *exit_page;

 public:
  NFCEMVReadPage(uint8_t _position_limit, uint8_t _lower_limit,
                      uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~NFCEMVReadPage();
  void display();

  void click(int pos, void callback()) { grid->click(pos, callback); };
  void set_selected(int pos, bool status) { grid->set_selected(pos, status); };
  void set_card_type(String type) {
    card_type->set_text(type);
  }
  void set_card_pan(String pan) {
    card_number->set_text(pan);
  }
  void set_card_issue_date(String issuedate) {
    issue_date->set_text(issuedate);
  }
  void set_card_expire_date(String expiredate) {
    expire->set_text(expiredate);
  }
};

#endif
