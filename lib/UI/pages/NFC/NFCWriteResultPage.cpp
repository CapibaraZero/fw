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

#include "NFCWriteResultPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/BLE/BLE_submenu_keys.h"

NFCWriteResultPage::NFCWriteResultPage(GFXForms *_screen) { screen = _screen; }

NFCWriteResultPage::~NFCWriteResultPage() {}

void NFCWriteResultPage::display() {
  nfc_grid = new Grid(screen, 4, 1);
  write_info = new Text(screen, ST77XX_WHITE, "Writing tag to another...");
  wrote_sectors = new Text(screen, ST77XX_WHITE, "Written sectors: 0");
  unwritable_sectors = new Text(screen, ST77XX_WHITE, "Unwritable sectors: 0");
  return_back = new List(screen, "Go back", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  exit_page = new List(screen, "Exit", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  nfc_grid->add(write_info);
  nfc_grid->add(wrote_sectors);
  nfc_grid->add(unwritable_sectors);
  nfc_grid->add(return_back);
  nfc_grid->add(exit_page);
  nfc_grid->set_y_spacing(20);
  nfc_grid->set_selected(3, true);
  nfc_grid->display();
}
