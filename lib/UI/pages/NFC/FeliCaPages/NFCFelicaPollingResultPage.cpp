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

#include "NFCFelicaPollingResultPage.hpp"

#include "../../../i18n.hpp"
#include "../../../i18n/NFC/nfc_felica_polling_page_keys.h"
#include "../../../navigation/NFC/NFCNavigation.hpp"
#include "gui.hpp"
#include "hex2str.hpp"

NFCFelicaPollingResultPage::~NFCFelicaPollingResultPage() {}

void NFCFelicaPollingResultPage::display(uint8_t *idm, uint8_t *pmm,
                                         uint16_t sys_code) {
  grid = new Grid(screen, 6, 1);
  tag_info = new Text(screen, ST77XX_WHITE,
                      english_words->at(NFC_FELICA_POLLING_TAG_FOUND_KEY), 2);
  idm_text = new Text(screen, ST77XX_WHITE,
                      english_words->at(NFC_FELICA_IDM_KEY) + hextostr(idm, 8));
  pmm_text = new Text(screen, ST77XX_WHITE,
                      english_words->at(NFC_FELICA_PMM_KEY) + hextostr(pmm, 8));
  sys_code_text = new Text(
      screen, ST77XX_WHITE,
      english_words->at(NFC_FELICA_SYSTEM_CODE_KEY) + String(sys_code, HEX));
  dump_to_sd = new List(screen, english_words->at(NFC_DUMP_TAG_TO_SD), 2,
                        ST77XX_WHITE, 20, ST77XX_BLACK, felica_dump);
  emulate_tag = new List(screen, "Emulate UID", 2, ST77XX_WHITE, 20, ST77XX_BLACK, emulate_iso18092);
  // write_tag = new List(screen, "Write tag", 2, ST77XX_WHITE, 20,
  // ST77XX_BLACK); format_tag = new List(screen,
  // english_words->at(NFC_FORMAT_TAG_TO_SD), 2,
  //                       ST77XX_WHITE, 20, ST77XX_BLACK);
  //   bruteforce_tag = new List(screen, "Bruteforce tag", 2, ST77XX_WHITE, 20,
  //   ST77XX_BLACK);
  exit_page = new List(screen, english_words->at(NFC_GO_BACK_KEY), 2,
                       ST77XX_WHITE, 20, ST77XX_BLACK, goto_home);
  grid->add(tag_info);
  grid->add(idm_text);
  grid->add(pmm_text);
  grid->add(sys_code_text);
  grid->add(dump_to_sd);
  // grid->add(write_tag);
  // grid->add(format_tag);
  //   grid->add(bruteforce_tag);
  grid->add(emulate_tag);
  grid->add(exit_page);
  grid->set_selected(4, true);
  grid->set_y_spacing(20);
  grid->display();
}
