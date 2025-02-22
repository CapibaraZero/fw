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

#include "NFCEMVReadPage.hpp"
#include "../../navigation/NFC/NFCNavigation.hpp"

#include "gui.hpp"

NFCEMVReadPage::~NFCEMVReadPage() {
  delete card_type;
  delete card_number;
  delete issue_date;
  delete expire;
}

void NFCEMVReadPage::display() {
  grid = new Grid(screen, 5, 1);
  card_type = new Text(screen, ST77XX_WHITE, "Scanning EMV...");
  card_number = new Text(screen, ST77XX_WHITE, "");
  issue_date = new Text(screen, ST77XX_WHITE, "");
  expire = new Text(screen, ST77XX_WHITE, "");
  exit_page = new List(screen, "Exit", 2, ST77XX_WHITE, 20,  ST77XX_BLUE, goto_home);
  grid->add(card_type);
  grid->add(card_number);
  grid->add(issue_date);
  grid->add(expire);
  grid->add(exit_page);
  grid->set_y_spacing(20);
  grid->set_selected(4, true);
  grid->display();
}
