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

#include "WifiSniffPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/wifi/wifi_sniff_keys.h"
#include "../../navigation/wifi/wifi_navigation.hpp"
#include "gui.hpp"

WifiSniffPage::~WifiSniffPage() {
  delete text;
  delete packet_count;
  delete save;
}

void WifiSniffPage::update_packet_count(int count) {
  packet_count->set_text(english_words->at(WIFI_SNIFFING_SNIFFED_KEY) +
                         String(count));
}

void WifiSniffPage::display() {
  text =
      new Text(screen, ST77XX_WHITE, english_words->at(WIFI_SNIFFING_INFO_KEY));
  packet_count =
      new Text(screen, ST77XX_WHITE,
               english_words->at(WIFI_SNIFFING_SNIFFED_KEY) + String(0));
  grid = new Grid(screen, 3, 1);
  save = new List(screen, english_words->at(WIFI_SNIFFING_SAVE_KEY), 2,
                  ST77XX_WHITE, 20, ST77XX_BLACK, stop_wifi_sniffer);
  grid->add(text);
  grid->add(packet_count);
  grid->add(save);
  grid->set_selected(2, true);
  grid->set_y_spacing(20);
  grid->display();
}