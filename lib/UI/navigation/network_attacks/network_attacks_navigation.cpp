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

#include "../navigation.hpp"
#include "gui.hpp"
#include "network_attacks.hpp"
#include "network_attacks_btn.hpp"

static Gui *gui;
static NetworkAttacks *attack;

void goto_net_attacks_gui() {
  gui->reset();
  gui->set_current_position(0);
  gui->init_network_attacks_gui();
}

void goto_dhcpglutton_gui() {
  gui->reset();
  gui->set_current_position(0);
  gui->init_dhcp_glutton_gui();
  start_dhcpglutton(gui, attack);
}

void goto_evilportal_gui() {
  gui->reset();
  gui->set_current_position(0);
  gui->init_evilportal_gui();
  start_evilportal(gui, attack);
}

static void goto_arp_poisoner_gui() {
  gui->reset();
  gui->set_current_position(0);
  gui->init_arp_poisoner_gui();
  start_arp_poisoning(gui, attack);
}

static void net_attacks_goto_home() {
  gui->destroy_network_attacks_gui();
  init_main_gui();
}

void network_attacks_submenu_handler(int pos) {
  switch (pos) {
    case 0:
      goto_dhcpglutton_gui();
      break;
    case 1:
      goto_evilportal_gui();
      break;
    case 2:
      goto_arp_poisoner_gui();
      break;
    case 3:
      net_attacks_goto_home();
      break;
    default:
      break;
  }
}

void stop_dhcpglutton() {
  kill_dhcpglutton();
  init_main_gui();
  gui->destroy_dhcp_glutton_gui();
}

void stop_evilportal() {
  kill_evilportal(attack);
  gui->destroy_evilportal_gui();
  init_main_gui();
}

void stop_arp_poisoner() {
  kill_arp_poisoning();
  gui->destroy_arp_poisoner_gui();
  init_main_gui();
}

void init_network_attacks_navigation(Gui *_gui) {
  gui = _gui;
  attack = new NetworkAttacks();
}
