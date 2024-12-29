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

#include "EvilPortalPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/network_attacks/evilportal_keys.h"
#include "../../navigation/wifi/wifi_navigation.hpp"
#include "gui.hpp"

EvilPortalPage::~EvilPortalPage() {
  delete text;
  delete portal_ip;
  delete client_count;
  delete save;
}

void EvilPortalPage::update_requests_count(int count) {
  client_count->set_text(english_words->at(EVILPORTAL_CAPTURED_REQUESTS_KEY) +
                         String(count));
}

void EvilPortalPage::set_portal_ip(String ip) {
  portal_ip->set_text(english_words->at(EVILPORTAL_IP_KEY) + ip);
}

void EvilPortalPage::display() {
  text =
      new Text(screen, ST77XX_WHITE, english_words->at(RUNNING_EVILPORTAL_KEY));
  portal_ip =
      new Text(screen, ST77XX_WHITE, english_words->at(EVILPORTAL_IP_KEY));
  client_count =
      new Text(screen, ST77XX_WHITE,
               english_words->at(EVILPORTAL_CAPTURED_REQUESTS_KEY) + String(0));
  grid = new Grid(screen, 4, 1);
  save = new List(screen, "Stop", 2, ST77XX_WHITE, 20, ST77XX_BLACK,
                  stop_evilportal);
  grid->add(text);
  grid->add(portal_ip);
  grid->add(client_count);
  grid->add(save);
  grid->set_selected(3, true);
  grid->set_y_spacing(20);
  grid->display();
}