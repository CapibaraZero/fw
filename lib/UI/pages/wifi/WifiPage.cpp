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

#include "WifiPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/wifi/wifi_submenu_keys.h"

WifiPage::WifiPage(GFXForms *_screen) { screen = _screen; }

WifiPage::~WifiPage() {}

void WifiPage::display() {
  wifi_grid = new Grid(screen, 3, 1);
  wifi_list = new List(screen, english_words->at(WIFI_SCAN_KEY), 2,
                       ST77XX_WHITE, 20, ST77XX_BLACK);
  wifi_sniff = new List(screen, english_words->at(WIFI_SNIFF_KEY), 2,
                        ST77XX_WHITE, 20, ST77XX_BLACK);
  go_back = new List(screen, english_words->at(WIFI_GO_BACK_KEY), 2,
                        ST77XX_WHITE, 20, ST77XX_BLACK);
  wifi_grid->add(wifi_list);
  wifi_grid->add(wifi_sniff);
  wifi_grid->add(go_back);
  wifi_grid->set_selected(0, true);
  wifi_grid->display();
}