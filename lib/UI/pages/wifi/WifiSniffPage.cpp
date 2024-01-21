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

#include "WifiSniffPage.hpp"
#include "../../i18n.hpp"
#include "../../i18n/wifi/wifi_sniff_keys.h"

WifiSniffPage::WifiSniffPage(GFXForms *_screen) {
  text = new Text(_screen, ST77XX_WHITE, english_words->at(WIFI_SNIFFING_INFO_KEY));
  packet_count = new Text(_screen, ST77XX_WHITE, english_words->at(WIFI_SNIFFING_SNIFFED_KEY) + String(0));
  details_grid = new Grid(_screen, 3, 1);
  save = new List(_screen, english_words->at(WIFI_SNIFFING_SAVE_KEY), 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  details_grid->add(text);
  details_grid->add(packet_count);
  details_grid->add(save);
  details_grid->set_selected(2, true);
  details_grid->set_y_spacing(20);
}

WifiSniffPage::~WifiSniffPage() {
}

void WifiSniffPage::update_packet_count(int count) {
  packet_count->set_text(english_words->at(WIFI_SNIFFING_SNIFFED_KEY) + String(count));
}
