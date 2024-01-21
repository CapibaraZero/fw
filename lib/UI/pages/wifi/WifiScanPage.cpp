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

#include "WifiScanPage.hpp"
#include "../../i18n.hpp"
#include "../../i18n/wifi/wifi_scan_keys.h"

WifiScanPage::WifiScanPage(GFXForms *_screen) {
    screen = _screen;
}

WifiScanPage::~WifiScanPage() {
}

void WifiScanPage::display() {
  wifi_scan_grid = new Grid(screen, 3, 1);
  wifi_scan_text = new Text(screen, ST77XX_WHITE, english_words->at(WIFI_SCANNING_KEY));
  wifi_scan_progress = new Text(screen, ST77XX_WHITE, "10%");
  wifi_scan_current_ch = new Text(screen, ST77XX_WHITE, "1");
  wifi_scan_grid->add(wifi_scan_text);
  wifi_scan_grid->add(wifi_scan_progress);
  wifi_scan_grid->add(wifi_scan_current_ch);
  wifi_scan_grid->set_y_spacing(30);
  wifi_scan_grid->display();
}