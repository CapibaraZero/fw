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

#include "NFCPollingResultPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/NFC/nfc_polling_result_page_keys.h"
#include "../../navigation/NFC/NFCNavigation.hpp"
#include "gui.hpp"
#include "hex2str.hpp"

NFCPollingResultPage::~NFCPollingResultPage() {
  delete tag_info;
  delete uid_text;
  delete bruteforce_tag;
  delete exit_page;
}

void NFCPollingResultPage::display(uint8_t *uid, uint8_t length,
                                   const char *tag_name) {
  grid = new Grid(screen, 5, 1);
  tag_info = new Text(screen, ST77XX_WHITE, tag_name, 2);
  uid_text = new Text(screen, ST77XX_WHITE,
                      english_words->at(NFC_UID_KEY) + hextostr(uid, length));
  write_tag = new List(screen, "Write tag", 2, ST77XX_WHITE, 20, ST77XX_BLACK,
                       open_nfc_dump_browser);
  format_tag = new List(screen, english_words->at(NFC_FORMAT_TAG_TO_SD), 2,
                        ST77XX_WHITE, 20, ST77XX_BLACK, format_nfc_tag);
  bruteforce_tag =
      new List(screen, english_words->at(NFC_BRUTEFORCE_TAG_KEY), 2,
               ST77XX_WHITE, 20, ST77XX_BLACK, bruteforce_a_tag);
  emulate_tag = new List(screen, "Emulate UID", 2, ST77XX_WHITE, 20, ST77XX_BLACK, emulate_iso14443a);
  exit_page = new List(screen, english_words->at(NFC_GO_BACK_KEY), 2,
                       ST77XX_WHITE, 20, ST77XX_BLACK, goto_home);
  grid->add(tag_info);
  grid->add(uid_text);
  grid->add(write_tag);
  grid->add(format_tag);
  grid->add(bruteforce_tag);
  grid->add(emulate_tag);
  grid->add(exit_page);
  grid->set_selected(2, true);
  grid->set_y_spacing(20);
  grid->display();
}
