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

#include "NFCDumpResultPage.hpp"

#include "../../navigation/NFC/NFCNavigation.hpp"
#include "gui.hpp"

NFCDumpResultPage::~NFCDumpResultPage() {
  delete dumping_to_sd;
  delete dumped_sectors;
  delete unreadable_sectors;
  delete unauthenticated_sectors;
  delete save_to_sd;
}

void NFCDumpResultPage::display() {
  grid = new Grid(screen, 6, 1);
  dumping_to_sd =
      new Text(screen, ST77XX_WHITE, english_words->at(NFC_DUMPING_TAG_KEY));
  dumped_sectors =
      new Text(screen, ST77XX_WHITE, english_words->at(NFC_DUMPED_SECTORS_KEY));
  unreadable_sectors = new Text(screen, ST77XX_WHITE,
                                english_words->at(NFC_UNREADABLE_SECTORS_KEY));
  unauthenticated_sectors = new Text(
      screen, ST77XX_WHITE, english_words->at(NFC_UNAUTHENTICATED_SECTORS_KEY));
  save_to_sd = new List(screen, english_words->at(NFC_SAVE_TO_SD_KEY), 2,
                        ST77XX_WHITE, 20, ST77XX_BLUE, save_dump_to_sd);
  // return_back = new List(screen, "Go back", 2, ST77XX_WHITE, 20,
  // ST77XX_BLACK); exit_page = new List(screen, "Exit", 2, ST77XX_WHITE, 20,
  // ST77XX_BLACK);
  grid->add(dumping_to_sd);
  grid->add(dumped_sectors);
  grid->add(unauthenticated_sectors);
  grid->add(unreadable_sectors);
  grid->add(save_to_sd);
  // grid->add(return_back);
  // grid->add(exit_page);
  grid->set_y_spacing(20);
  grid->set_selected(4, true);
  grid->display();
}
