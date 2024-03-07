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
#include "../../i18n/NFC/nfc_bruteforce_page_key.h"

#ifndef NFC_BRUTEFORCE_TAG_PAGE_H
#define NFC_BRUTEFORCE_TAG_PAGE_H

class NFCBruteforceTagPage : public Page {
 private:
  Text *bruteforce_info;
  Text *tried_keys;
  Text *found_keys;
  List *return_back;
  List *exit_page;
  Grid *nfc_grid;
  uint8_t total_keys;

 public:
  NFCBruteforceTagPage(GFXForms *_screen);
  ~NFCBruteforceTagPage();
  void display();
  void up(){};
  void down(){};
  void left(){};
  void right(){};
  void click(int pos, void callback()) {
    nfc_grid->click(pos, callback);
  };
  void set_selected(int pos, bool status) {
    nfc_grid->set_selected(pos, status);
  };
  void update_tried_keys(int keys) {
    tried_keys->set_text((String)"Tried keys: " + (String) keys);
  }
  void set_found_key(bool found) {
    if(found)
      found_keys->set_color(ST77XX_WHITE);
    else {
      found_keys->set_text("Can't find key");
      found_keys->set_color(ST77XX_WHITE);
    }
  }
};

#endif
