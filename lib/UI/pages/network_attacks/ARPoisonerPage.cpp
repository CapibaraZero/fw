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

#include "ARPoisonerPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/network_attacks/dhcpglutton_keys.h"
#include "../../navigation/wifi/wifi_navigation.hpp"
#include "gui.hpp"

ARPoisonerPage::~ARPoisonerPage() {
  delete text;
  delete stop;
}

void ARPoisonerPage::display() {
  grid = new Grid(screen, 2, 1);
  text = new Text(screen, ST77XX_WHITE, "ARP poisoning running");
  stop = new List(screen, "Stop", 2, ST77XX_WHITE, 20, ST77XX_BLACK,
                  stop_arp_poisoner);

  grid->add(text);
  grid->add(stop);
  grid->set_selected(1, true);
  grid->set_y_spacing(20);
  grid->display();
}