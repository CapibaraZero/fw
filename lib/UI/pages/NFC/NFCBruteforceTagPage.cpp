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

#include "NFCBruteforceTagPage.hpp"

#include "../../i18n.hpp"

NFCBruteforceTagPage::NFCBruteforceTagPage(GFXForms *_screen) {
  screen = _screen;
}

NFCBruteforceTagPage::~NFCBruteforceTagPage() {}

void NFCBruteforceTagPage::display() {
  nfc_grid = new Grid(screen, 3, 1);
  bruteforce_info = new Text(screen, ST77XX_WHITE,
                             english_words->at(NFC_BRUTEFORCING_TAG_KEY));
  tried_keys =
      new Text(screen, ST77XX_WHITE, english_words->at(NFC_TRIED_KEYS_KEY));
  found_keys =
      new Text(screen, ST77XX_BLACK, english_words->at(NFC_FOUND_KEYS_KEY));
  // return_back = new List(screen, "Go back", 2, ST77XX_WHITE, 20,
  // ST77XX_BLACK); exit_page = new List(screen, "Exit", 2, ST77XX_WHITE, 20,
  // ST77XX_BLUE);
  nfc_grid->add(bruteforce_info);
  nfc_grid->add(tried_keys);
  nfc_grid->add(found_keys);
  // nfc_grid->add(return_back);
  // nfc_grid->add(exit_page);
  nfc_grid->set_y_spacing(20);
  // nfc_grid->set_selected(3, true);
  nfc_grid->display();
}
