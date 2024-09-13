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

#include "NFCFormatResultPage.hpp"

#include "gui.hpp"

NFCFormatResultPage::~NFCFormatResultPage() {
  delete dumping_to_sd;
  delete formatted_sectors;
  delete unauthenticated_sectors;
}

void NFCFormatResultPage::display() {
  grid = new Grid(screen, 3, 1);
  dumping_to_sd =
      new Text(screen, ST77XX_WHITE, english_words->at(NFC_FORMATTING_TAG_KEY));
  formatted_sectors = new Text(screen, ST77XX_WHITE,
                               english_words->at(NFC_FORMATTED_SECTORS_KEY));
  unauthenticated_sectors = new Text(
      screen, ST77XX_WHITE, english_words->at(NFC_UNAUTHENTICATED_SECTORS_KEY));
  // return_back = new List(screen, "Go back", 2, ST77XX_WHITE, 20,
  // ST77XX_BLACK); exit_page = new List(screen, "Exit", 2, ST77XX_WHITE, 20,
  // ST77XX_BLUE);
  grid->add(dumping_to_sd);
  grid->add(formatted_sectors);
  grid->add(unauthenticated_sectors);
  // grid->add(return_back);
  // grid->add(exit_page);
  grid->set_y_spacing(20);
  // grid->set_selected(3, true);
  grid->display();
}
