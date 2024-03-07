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

#include "NFCPollingResultPage.hpp"
#include "../../i18n.hpp"
#include "../../i18n/NFC/nfc_polling_result_page_keys.h"
#include "hex2str.hpp"

NFCPollingResultPage::NFCPollingResultPage(GFXForms *_screen) {
  screen = _screen;
}

NFCPollingResultPage::~NFCPollingResultPage() {
}

void NFCPollingResultPage::display(uint8_t *uid, uint8_t length) {
  nfc_grid = new Grid(screen, 6, 1);
  if(length == 4)
    tag_info = new Text(screen, ST77XX_WHITE, english_words->at(NFC_MIFARE_CLASSIC_FOUND_KEY));
  else
    tag_info = new Text(screen, ST77XX_WHITE, english_words->at(NFC_MIFARE_ULTRALIGHT_FOUND_KEY), 2);
  uid_text = new Text(screen, ST77XX_WHITE, english_words->at(NFC_UID_KEY) + hextostr(uid, length));
  dump_to_sd = new List(screen, english_words->at(NFC_DUMP_TAG_TO_SD), 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  // write_tag = new List(screen, "Write tag", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  format_tag = new List(screen, english_words->at(NFC_FORMAT_TAG_TO_SD), 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  bruteforce_tag = new List(screen, english_words->at(NFC_BRUTEFORCE_TAG_KEY), 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  exit_page = new List(screen, english_words->at(NFC_GO_BACK_KEY), 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  nfc_grid->add(tag_info);
  nfc_grid->add(uid_text);
  nfc_grid->add(dump_to_sd);
  // nfc_grid->add(write_tag);
  // nfc_grid->add(format_tag);
  nfc_grid->add(bruteforce_tag);
  nfc_grid->add(exit_page);
  nfc_grid->set_selected(2, true);
  nfc_grid->set_y_spacing(20);
  nfc_grid->display();
}
