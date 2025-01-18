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

#include "WifiScanPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/wifi/wifi_scan_keys.h"
#include "gui.hpp"

WifiScanPage::~WifiScanPage() {
  delete wifi_scan_text;
  delete wifi_scan_progress;
  delete wifi_scan_current_ch;
}

void WifiScanPage::display() {
  grid = new Grid(screen, 3, 1);
  wifi_scan_text =
      new Text(screen, ST77XX_WHITE, english_words->at(WIFI_SCANNING_KEY));
  wifi_scan_progress = new Text(screen, ST77XX_WHITE, "0%");
  wifi_scan_current_ch = new Text(screen, ST77XX_WHITE, "Initializing WiFi stack...", 2, true);
  grid->add(wifi_scan_text);
  grid->add(wifi_scan_progress);
  grid->add(wifi_scan_current_ch);
  grid->set_y_spacing(10);
  grid->display();
}