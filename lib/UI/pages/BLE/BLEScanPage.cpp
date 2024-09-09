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

#include "BLEScanPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/BLE/ble_scan_keys.h"
#include "gui.hpp"

BLEScanPage::~BLEScanPage() {
  delete ble_scan_adv_devices;
  delete ble_scan_progress;
  delete ble_scan_text;
}

void BLEScanPage::display() {
  grid = new Grid(screen, 3, 1);
  ble_scan_text =
      new Text(screen, ST77XX_WHITE, english_words->at(BLE_SCANNING_KEY));
  ble_scan_progress = new Text(screen, ST77XX_WHITE, "10%");
  ble_scan_adv_devices = new Text(screen, ST77XX_WHITE, "0");
  grid->add(ble_scan_text);
  grid->add(ble_scan_progress);
  grid->add(ble_scan_adv_devices);
  grid->set_y_spacing(30);
  grid->display();
}
