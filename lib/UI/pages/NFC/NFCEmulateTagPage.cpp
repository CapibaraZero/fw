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

#include "NFCEmulateTagPage.hpp"
#include "../../navigation/NFC/NFCNavigation.hpp"

#include "gui.hpp"

NFCEmulateTagPage::~NFCEmulateTagPage() {
  delete emulate_text;
  delete exit_page;
}

void NFCEmulateTagPage::display() {
  grid = new Grid(screen, 2, 1);
  emulate_text =
      new Text(screen, ST77XX_WHITE, "Emulating tag...");
  exit_page = new List(screen, "Exit", 2, ST77XX_WHITE, 20, ST77XX_BLACK, goto_home);
  grid->add(emulate_text);
  grid->add(exit_page);
  grid->set_y_spacing(20);
  grid->set_selected(1, true);
  grid->display();
}
