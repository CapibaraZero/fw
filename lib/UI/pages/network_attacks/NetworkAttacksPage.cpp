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

#include "NetworkAttacksPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/network_attacks/net_attacks_main_page.h"

NetworkAttacksPage::NetworkAttacksPage(GFXForms *_screen) { screen = _screen; }

NetworkAttacksPage::~NetworkAttacksPage() {}

void NetworkAttacksPage::display() {
  net_attacks_grid = new Grid(screen, 1, 1);
  evilportal = new List(screen, english_words->at(EVILPORTAL_KEY), 2,
                        ST77XX_WHITE, 20, ST77XX_BLACK);
  dhcpglutton = new List(screen, english_words->at(DHCP_GLUTTON_KEY), 2,
                         ST77XX_WHITE, 20, ST77XX_BLACK);
  net_attacks_grid->add(dhcpglutton);
  net_attacks_grid->add(evilportal);
  net_attacks_grid->set_selected(0, true);
  net_attacks_grid->display();
}
