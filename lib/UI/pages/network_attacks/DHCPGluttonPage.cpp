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

#include "DHCPGluttonPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/network_attacks/dhcpglutton_keys.h"

DHCPGluttonPage::DHCPGluttonPage(GFXForms *_screen) {
  text = new Text(_screen, ST77XX_WHITE,
                  english_words->at(RUNNING_DHCPGLUTTON_KEY));
  client_count =
      new Text(_screen, ST77XX_WHITE,
               english_words->at(CREATED_DHCPGLUTTON_CLIENTS_KEY) + String(0));
  details_grid = new Grid(_screen, 3, 1);
  save = new List(_screen, "Stop", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  details_grid->add(text);
  details_grid->add(client_count);
  details_grid->add(save);
  details_grid->set_selected(2, true);
  details_grid->set_y_spacing(20);
}

DHCPGluttonPage::~DHCPGluttonPage() {}

void DHCPGluttonPage::update_packet_count(int count) {
  client_count->set_text(english_words->at(CREATED_DHCPGLUTTON_CLIENTS_KEY) +
                         String(count));
}
