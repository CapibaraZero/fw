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

BLEPage::BLEPage(GFXForms *_screen) { screen = _screen; }

BLEPage::~BLEPage() {}

void BLEPage::display() {
    ble_grid = new Grid(screen, 5, 1);
    //  ble_list = new List(screen, english_words->at(BLE_SCAN_KEY), 2,
    //  ST77XX_WHITE, 20, ST77XX_BLACK);
    ble_sniff = new List(screen, english_words->at(BLE_SNIFF_KEY), 2,
                         ST77XX_WHITE, 20, ST77XX_BLACK);
    apple_juice =
        new List(screen, "AppleJuice", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
    samsung_ble =
        new List(screen, "Samsung BLE spam", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
    swift_pair =
        new List(screen, "Swift pair spam", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
    fast_pair = new List(screen, "Fast pair spam", 2, ST77XX_WHITE, 20,
                         ST77XX_BLACK);
    go_back = new List(screen, english_words->at(BLE_GO_BACK_KEY), 2, ST77XX_WHITE,
                       20, ST77XX_BLACK);
    //  ble_grid->add(ble_list);
    ble_grid->add(ble_sniff);
    ble_grid->add(apple_juice);
    ble_grid->add(samsung_ble);
    ble_grid->add(swift_pair);
    ble_grid->add(fast_pair);
    ble_grid->add(go_back);
    ble_grid->set_selected(0, true);
    ble_grid->display();
}
