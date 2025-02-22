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

#include "BLEPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/BLE/BLE_submenu_keys.h"
#include "../../navigation/BLE/ble_navigation.hpp"
#include "gui.hpp"

BLEPage::~BLEPage() {
  delete ble_sniff;
  delete apple_juice;
  delete samsung_ble;
  delete swift_pair;
  delete fast_pair;
  delete go_back;
}

void BLEPage::display() {
  grid = new Grid(screen, 5, 1);
  //  ble_list = new List(screen, english_words->at(BLE_SCAN_KEY), 2,
  //  ST77XX_WHITE, 20, ST77XX_BLACK);
  ble_sniff = new List(screen, english_words->at(BLE_SNIFF_KEY), 2,
                       ST77XX_WHITE, 20, ST77XX_BLACK, goto_ble_sniff_gui);
  apple_juice = new List(screen, "AppleJuice", 2, ST77XX_WHITE, 20,
                         ST77XX_BLACK, goto_applejuice);
  samsung_ble = new List(screen, "Samsung BLE spam", 2, ST77XX_WHITE, 20,
                         ST77XX_BLACK, goto_samsung_spam);
  swift_pair = new List(screen, "Swift pair spam", 2, ST77XX_WHITE, 20,
                        ST77XX_BLACK, goto_swift_spam);
  fast_pair = new List(screen, "Fast pair spam", 2, ST77XX_WHITE, 20,
                       ST77XX_BLACK, goto_fastpair_spam);
  go_back = new List(screen, english_words->at(BLE_GO_BACK_KEY), 2,
                     ST77XX_WHITE, 20, ST77XX_BLACK, ble_goto_home);
  //  grid->add(ble_list);
  grid->add(ble_sniff);
  grid->add(apple_juice);
  grid->add(samsung_ble);
  grid->add(swift_pair);
  grid->add(fast_pair);
  grid->add(go_back);
  grid->set_selected(0, true);
  grid->display();
}
