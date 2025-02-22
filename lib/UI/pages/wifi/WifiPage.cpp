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
#include "../../i18n/network_attacks/net_attacks_main_page.h"
#include "../../navigation/wifi/wifi_navigation.hpp"
#include "../../navigation/wifi/wifi_navigation.hpp"
#include "gui.hpp"

WifiPage::~WifiPage() {
  delete wifi_list;
  delete wifi_sniff;
  delete go_back;
}

void WifiPage::display() {
  grid = new Grid(screen, 7, 1);
  wifi_list = new List(screen, english_words->at(WIFI_SCAN_KEY), 2,
                       ST77XX_WHITE, 20, ST77XX_BLACK, goto_scan_wifi);
  wifi_sniff = new List(screen, english_words->at(WIFI_SNIFF_KEY), 2,
                        ST77XX_WHITE, 20, ST77XX_BLACK, goto_sniff_wifi);
  go_back = new List(screen, english_words->at(WIFI_GO_BACK_KEY), 2,
                     ST77XX_WHITE, 20, ST77XX_BLACK, wifi_goto_home);
  evilportal = new List(screen, english_words->at(EVILPORTAL_KEY), 2,
                        ST77XX_WHITE, 20, ST77XX_BLACK, goto_evilportal_gui);
  dhcpglutton = new List(screen, english_words->at(DHCP_GLUTTON_KEY), 2,
                         ST77XX_WHITE, 20, ST77XX_BLACK, goto_dhcpglutton_gui);
  arp_poisoner = new List(screen, "ARPoisoner", 2, ST77XX_WHITE, 20,
                          ST77XX_BLACK, goto_arp_poisoner_gui);
  go_back = new List(screen, english_words->at(NET_ATTACK_GO_BACK_KEY), 2,
                     ST77XX_WHITE, 20, ST77XX_BLACK, net_attacks_goto_home);
  grid->add(wifi_list);
  grid->add(wifi_sniff);
  grid->add(dhcpglutton);
  grid->add(evilportal);
  grid->add(arp_poisoner);
  grid->add(go_back);
  grid->set_selected(0, true);
  grid->display();
}