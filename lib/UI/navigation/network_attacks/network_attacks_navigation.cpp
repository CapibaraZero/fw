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
#include "pages/network_attacks/DHCPGluttonPage.hpp"
#include "pages/network_attacks/EvilPortalPage.hpp"
#include "pages/network_attacks/NetworkAttacksPage.hpp"
#include "pages/network_attacks/ARPoisonerPage.hpp"

static Gui *gui;
static NetworkAttacks *attack;
static NetworkAttacksPage *net_attacks_page;
static DHCPGluttonPage *dhcp_glutton_page;
static EvilPortalPage *evilportal_page;
static ARPoisonerPage *arpoisoner_page;

void goto_net_attacks_gui() {
    gui->reset();
    net_attacks_page = new NetworkAttacksPage(3, 0, 1, gui->get_screen(), gui);
    gui->set_current_page(net_attacks_page);
}

void goto_dhcpglutton_gui() {
    gui->reset();
    dhcp_glutton_page = new DHCPGluttonPage(0, 0, 0, gui->get_screen(), gui);
    gui->set_current_page(dhcp_glutton_page);
    start_dhcpglutton(gui, attack);
}

void goto_evilportal_gui() {
    gui->reset();
    evilportal_page = new EvilPortalPage(0, 0, 0, gui->get_screen(), gui);
    gui->set_current_page(evilportal_page);
    start_evilportal(gui, attack);
}

void goto_arp_poisoner_gui() {
    gui->reset();
    arpoisoner_page = new ARPoisonerPage(0, 0, 0, gui->get_screen(), gui);
    gui->set_current_page(arpoisoner_page);
    start_arp_poisoning(gui, attack);
}

void set_dhcp_glutton_clients(int client) {
  dhcp_glutton_page->update_packet_count(client);
}

void set_evilportal_ip(const char *ip) {
    evilportal_page->set_portal_ip(ip);
}

void set_evilportal_requests(int req) {
  evilportal_page->update_requests_count(req);
}

void net_attacks_goto_home() {
    init_main_gui();
    net_attacks_page = nullptr;
}

void stop_dhcpglutton() {
    kill_dhcpglutton();
    init_main_gui();
    dhcp_glutton_page = nullptr;
}

void stop_evilportal() {
    kill_evilportal(attack);
    init_main_gui();
    evilportal_page = nullptr;
}

void stop_arp_poisoner() {
    kill_arp_poisoning();
    init_main_gui();
    arpoisoner_page = nullptr;
}

void init_network_attacks_navigation(Gui *_gui) {
    gui = _gui;
    attack = new NetworkAttacks();
}
