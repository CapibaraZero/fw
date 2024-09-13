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

#ifndef NETWORK_ATTACKS_NAVIGATION_H
#define NETWORK_ATTACKS_NAVIGATION_H

#include "gui.hpp"

void goto_net_attacks_gui();
void stop_dhcpglutton();
void stop_evilportal();
void stop_arp_poisoner();
void init_network_attacks_navigation(Gui *_gui);
void goto_dhcpglutton_gui();
void goto_evilportal_gui();
void goto_arp_poisoner_gui();
void net_attacks_goto_home();
void set_dhcp_glutton_clients(int client);
void set_evilportal_ip(const char *ip);
void set_evilportal_requests(int req);
#endif
