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
#include "../../navigation/wifi/wifi_navigation.hpp"
#include "gui.hpp"

DHCPGluttonPage::~DHCPGluttonPage() {
  delete text;
  delete client_count;
  delete save;
}

void DHCPGluttonPage::update_packet_count(int count) {
  client_count->set_text(english_words->at(CREATED_DHCPGLUTTON_CLIENTS_KEY) +
                         String(count));
}

void DHCPGluttonPage::display() {
  text = new Text(screen, ST77XX_WHITE,
                  english_words->at(RUNNING_DHCPGLUTTON_KEY));
  client_count =
      new Text(screen, ST77XX_WHITE,
               english_words->at(CREATED_DHCPGLUTTON_CLIENTS_KEY) + String(0));
  grid = new Grid(screen, 3, 1);
  save = new List(screen, "Stop", 2, ST77XX_WHITE, 20, ST77XX_BLACK,
                  stop_dhcpglutton);
  grid->add(text);
  grid->add(client_count);
  grid->add(save);
  grid->set_selected(2, true);
  grid->set_y_spacing(20);
  grid->display();
}
