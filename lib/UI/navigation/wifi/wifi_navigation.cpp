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

#include <Arduino.h>

#include "../../../../include/debug.h"
#include "../navigation.hpp"
#include "gui.hpp"
#include "pages/wifi/WifiNetworksPage.hpp"
#include "pages/wifi/WifiPage.hpp"
#include "pages/wifi/WifiScanPage.hpp"
#include "pages/wifi/WifiScanSaveResultPage.hpp"
#include "pages/wifi/WifiSniffPage.hpp"
#include "wifi_attacks_btn.hpp"
#include "wifi_position.h"
#include "wifi_tasks.hpp"
#include "network_attacks.hpp"
#include "network_attacks_btn.hpp"
#include "pages/network_attacks/ARPoisonerPage.hpp"
#include "pages/network_attacks/DHCPGluttonPage.hpp"
#include "pages/network_attacks/EvilPortalPage.hpp"
#include "posixsd.hpp"

static Gui *gui;
WifiAttack wifiAttack = WifiAttack();
static WifiPage *wifi_page = nullptr;
static WifiScanPage *wifi_scan_page = nullptr;
static WifiSniffPage *wifi_sniff_page = nullptr;
static WifiNetworksPage *wifi_networks_page = nullptr;
static WifiScanSaveResultPage *wifi_save_result_page = nullptr;

void init_wifi_scan_gui() {
  wifi_scan_page = new WifiScanPage(0, 0, 0, gui->get_screen());
  gui->set_current_page(wifi_scan_page);
  wifi_page = nullptr;
}

void goto_scan_wifi() {
  gui->reset();
  init_wifi_scan_gui();
  scan_wifi(gui, &wifiAttack);
}

void goto_sniff_wifi() { sniff_wifi(gui, &wifiAttack); }

void init_wifi_gui() {
  gui->reset();
  wifi_page = new WifiPage(5, 0, 1, gui->get_screen());
  gui->set_current_page(wifi_page);
}

// Clean all pointers to avoid issues with memory area
// The pages is removed by GUI class
void wifi_cleanup() {
  wifi_page = nullptr;
  wifi_scan_page = nullptr;
  wifi_networks_page = nullptr;
  wifi_save_result_page = nullptr;
  wifi_sniff_page = nullptr;
}

/// @brief Update scanned WiFi channel
/// @param channel Channel to display in text
void set_wifi_channel_text(char *channel) {
  wifi_scan_page->set_ch_text(channel);
}

/// @brief Update WiFi scan progress
/// @param progress
void set_progress(char *progress) { wifi_scan_page->update_progress(progress); }

void wifi_goto_home() {
  wifi_cleanup();
  init_main_gui();
}

void stop_wifi_sniffer() {
#ifdef CONFIG_DEBUG_WIFI_MENU
  LOG_INFO("Sniff menu");
#endif
  /* Stop sniffer */
  wifiAttack.stop_sniff();
  stop_wifi_sniffer_updater();  // Delete updater task to avoid UI crash
  wifiAttack.clean_networks();
  wifi_cleanup();
  init_main_gui();
}

void save_wifi_scan_to_sd() {
  // Save to SD
  wifiAttack.save_scan();  // TODO: Create a task for this to create better UX
  wifiAttack.clean_networks();  // Clean previous scan
  wifi_cleanup();               // Remove WiFi pages
  init_main_gui();
}

void sniff_only_bssid() {
  gui->reset();
  wifi_sniff_page = new WifiSniffPage(2, 2, 0, gui->get_screen());
  gui->set_current_page(wifi_sniff_page);
  sniff_bssid(gui, &wifiAttack);
}

void init_wifi_networks_gui(vector<WifiNetwork> *networks) {
  if (wifi_networks_page == nullptr) /* We can use this page again, so no need
                                        to recreate a new one */
    // wifi_networks_page = new WifiNetworksPage(screen, networks);
    wifi_networks_page =
        new WifiNetworksPage(0, 0, 0, gui->get_screen(), networks);
  gui->set_current_page(wifi_networks_page);
  wifi_scan_page = nullptr;
}

/// @brief Get selected network in WiFi scan selection
/// @return selected network in WiFi scan selection
WifiNetwork get_current_network() {
  return wifi_networks_page->get_current_network();
}

void show_wifi_scan_result_dialog(bool empty) {
  if (wifi_networks_page != nullptr) {
    gui->reset();
    // wifi_save_result_page = new WifiScanSaveResultPage(screen, this,
    // empty);
    wifi_save_result_page =
        new WifiScanSaveResultPage(0, 0, 0, gui->get_screen());
    wifi_save_result_page->display(empty);
    gui->set_current_page(wifi_save_result_page, false);
    return;
  }
}

/// @brief Destroy WiFI scan result page
void destroy_wifi_scan_result() {
  // delete wifi_save_result_page;
  wifi_save_result_page = nullptr;
}

void go_back_to_net_list() {
  // Go back to networks list
  gui->reset();
  destroy_wifi_scan_result();  // We need to trigger
                               // get_wifi_scan_result_visible. TODO:
                               // Evaluate if it would be better to use
                               // another way to trigger that function
  init_wifi_networks_gui(
      nullptr);  // Pass nullptr since this page is already created
}

void show_wifi_sniff_page() {
  wifi_sniff_page = new WifiSniffPage(2, 2, 0, gui->get_screen());
  gui->set_current_page(wifi_sniff_page);
}

void display_wifi_scan_result() {
  show_wifi_scan_result_dialog(wifiAttack.get_networks().size() == 0);
}

/// @brief Update sniffed packets in WiFi sniffer page
/// @param count Number of sniffed packets
void update_packets_count(int count) {
  wifi_sniff_page->update_packet_count(count);
}


static NetworkAttacks *attack;
static DHCPGluttonPage *dhcp_glutton_page;
static EvilPortalPage *evilportal_page;
static ARPoisonerPage *arpoisoner_page;

void goto_dhcpglutton_gui() {
  if(!exists("/dhcp_glutton/config.json")) {
    gui->show_error_page("Missing config");
    init_wifi_gui();
    return;
  }
  gui->reset();
  dhcp_glutton_page = new DHCPGluttonPage(0, 0, 0, gui->get_screen());
  gui->set_current_page(dhcp_glutton_page);
  start_dhcpglutton(gui, attack);
}

void goto_evilportal_gui() {
  gui->reset();
  evilportal_page = new EvilPortalPage(0, 0, 0, gui->get_screen());
  gui->set_current_page(evilportal_page);
  start_evilportal(gui, attack);
}

void goto_arp_poisoner_gui() {
  if(!exists("/arp_poisoner/config.json")) {
    gui->show_error_page("Missing config");
    init_wifi_gui();
    return;
  }
  gui->reset();
  arpoisoner_page = new ARPoisonerPage(0, 0, 0, gui->get_screen());
  gui->set_current_page(arpoisoner_page);
  start_arp_poisoning(gui, attack);
}

void set_dhcp_glutton_clients(int client) {
  dhcp_glutton_page->update_packet_count(client);
}

void set_evilportal_ip(const char *ip) { evilportal_page->set_portal_ip(ip); }

void set_evilportal_requests(int req) {
  evilportal_page->update_requests_count(req);
}

void net_attacks_goto_home() {
  init_main_gui();
  // net_attacks_page = nullptr;
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

void init_wifi_navigation(Gui *_gui) { 
  gui = _gui;
  attack = new NetworkAttacks();
}
