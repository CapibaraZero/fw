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

#include "NFCDumpResultPage.hpp"

NFCDumpResultPage::NFCDumpResultPage(GFXForms *_screen) {
  screen = _screen;
}

NFCDumpResultPage::~NFCDumpResultPage() {
}

void NFCDumpResultPage::display() {
  nfc_grid = new Grid(screen, 6, 1);
  dumping_to_sd = new Text(screen, ST77XX_WHITE, english_words->at(NFC_DUMPING_TAG_KEY));
  dumped_sectors = new Text(screen, ST77XX_WHITE, english_words->at(NFC_DUMPED_SECTORS_KEY));
  unreadable_sectors = new Text(screen, ST77XX_WHITE, english_words->at(NFC_UNREADABLE_SECTORS_KEY));
  unauthenticated_sectors = new Text(screen, ST77XX_WHITE, english_words->at(NFC_UNAUTHENTICATED_SECTORS_KEY));
  save_to_sd = new List(screen, english_words->at(NFC_SAVE_TO_SD_KEY), 2, ST77XX_WHITE, 20, ST77XX_BLUE);
  // return_back = new List(screen, "Go back", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  // exit_page = new List(screen, "Exit", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  nfc_grid->add(dumping_to_sd);
  nfc_grid->add(dumped_sectors);
  nfc_grid->add(unauthenticated_sectors);
  nfc_grid->add(unreadable_sectors);
  nfc_grid->add(save_to_sd);
  // nfc_grid->add(return_back);
  // nfc_grid->add(exit_page);
  nfc_grid->set_y_spacing(20);
  // nfc_grid->set_selected(3, true);
  nfc_grid->display();
}
