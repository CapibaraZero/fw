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

#include "NFCMainPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/NFC/nfc_main_page_keys.h"

NFCMainPage::NFCMainPage(GFXForms *_screen) { screen = _screen; }

NFCMainPage::~NFCMainPage() {}

void NFCMainPage::display() {
  nfc_grid = new Grid(screen, 3, 1);
  polling_iso14443_a =
      new List(screen, english_words->at(POLLING_ISO14443A_KEY), 2,
               ST77XX_WHITE, 20, ST77XX_BLACK);
  polling_felica = new List(screen, english_words->at(POLLING_ISO18092_KEY), 2,
                            ST77XX_WHITE, 20, ST77XX_BLACK);
  go_back = new List(screen, english_words->at(NFC_POLLING_GO_BACK_KEY), 2,
                     ST77XX_WHITE, 20, ST77XX_BLACK);
  nfc_grid->add(polling_iso14443_a);
  nfc_grid->add(polling_felica);
  nfc_grid->add(go_back);
  nfc_grid->set_selected(0, true);
  nfc_grid->display();
}
