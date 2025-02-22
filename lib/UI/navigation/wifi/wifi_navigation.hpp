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

#ifndef WIFI_NAVIGATION_H
#define WIFI_NAVIGATION_H

#include "gui.hpp"
#include "wifi_attack.hpp"

void init_wifi_gui();

void stop_wifi_sniffer();

void display_wifi_scan_result();

void init_wifi_navigation(Gui *_gui);
void goto_scan_wifi();
void goto_sniff_wifi();
void wifi_goto_home();
void save_wifi_scan_to_sd();

void sniff_only_bssid();

void go_back_to_net_list();
/// @brief Update scanned WiFi channel
/// @param channel Channel to display in text
void set_wifi_channel_text(char *channel);

/// @brief Update WiFi scan progress
/// @param progress
void set_progress(char *progress);
void init_wifi_networks_gui(vector<WifiNetwork> *networks);
/// @brief Get selected network in WiFi scan selection
/// @return selected network in WiFi scan selection
WifiNetwork get_current_network();
/// @brief Create a WiFi scan final dialog(save to SD, sniff BSSID, go back or
/// return)
void show_wifi_scan_result_dialog(bool empty);
/// @brief Show sniffer page
void show_wifi_sniff_page();
/// @brief Update sniffed packets in WiFi sniffer page
/// @param count Number of sniffed packets
void update_packets_count(int count);

void goto_dhcpglutton_gui();

void goto_evilportal_gui();

void goto_arp_poisoner_gui();

void set_dhcp_glutton_clients(int client);

void set_evilportal_ip(const char *ip);
void set_evilportal_requests(int req);

void net_attacks_goto_home();

void stop_dhcpglutton();

void stop_evilportal();

void stop_arp_poisoner();
#endif
