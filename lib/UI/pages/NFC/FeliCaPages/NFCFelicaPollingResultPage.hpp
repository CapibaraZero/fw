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
#include "../../Page.hpp"

#ifndef NFC_FELICA_POLLING_RESULT_PAGE_H
#define NFC_FELICA_POLLING_RESULT_PAGE_H

class NFCFelicaPollingResultPage : public Page {
 private:
  Text *tag_info;
  Text *idm_text;
  Text *pmm_text;
  Text *sys_code_text;
  List *dump_to_sd;
  List *write_tag;
  List *format_tag;
  List *bruteforce_tag;
  List *exit_page;
  Grid *nfc_grid;

 public:
  NFCFelicaPollingResultPage(GFXForms *_screen);
  ~NFCFelicaPollingResultPage();
  void display(){
    nfc_grid->display();
  };
  void display(uint8_t *idm, uint8_t *pmm, uint16_t sys_code);
  void up(){};
  void down(){};
  void left(){};
  void right(){};
  void set_selected(int pos, bool status) {
    nfc_grid->set_selected(pos, status);
  };
  void click(int pos, void callback()) {
    nfc_grid->click(pos, callback);
  };
};

#endif
