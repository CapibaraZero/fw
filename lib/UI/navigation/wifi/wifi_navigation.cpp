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
#include "wifi_attacks_btn.hpp"
#include "wifi_position.h"
#include "wifi_tasks.hpp"
#include "pages/wifi/WifiNetworksPage.hpp"
#include "pages/wifi/WifiPage.hpp"
#include "pages/wifi/WifiScanPage.hpp"
#include "pages/wifi/WifiScanSaveResultPage.hpp"
#include "pages/wifi/WifiSniffPage.hpp"

static Gui *gui;
static WifiAttack wifiAttack = WifiAttack();
static WifiPage *wifi_page = nullptr;
static WifiScanPage *wifi_scan_page = nullptr;
static WifiSniffPage *wifi_sniff_page = nullptr;
static WifiNetworksPage *wifi_networks_page = nullptr;
static WifiScanSaveResultPage *wifi_save_result_page = nullptr;

void init_wifi_scan_gui() {
    delete wifi_page;  // Free some spaces
    wifi_page = nullptr;
    wifi_scan_page = new WifiScanPage(0, 0, 0, gui->get_screen(), gui);
    wifi_scan_page->display();
}

void goto_scan_wifi() {
    gui->reset();
    init_wifi_scan_gui();
    scan_wifi(gui, &wifiAttack);
}

void goto_sniff_wifi() { sniff_wifi(gui, &wifiAttack); }

void init_wifi_gui() {
    gui->reset();
    wifi_page = new WifiPage(2, 0, 1, gui->get_screen(), gui);
    wifi_page->display();
    gui->set_current_page(wifi_page);
}

void wifi_cleanup() {
    if (wifi_page != nullptr) {
        delete wifi_page;
        wifi_page = nullptr;
    }

    if (wifi_scan_page != nullptr) {
        delete wifi_scan_page;
        wifi_scan_page = nullptr;
    }

    if (wifi_networks_page != nullptr) {
      delete wifi_networks_page;
      wifi_networks_page = nullptr;
    }

    if (wifi_save_result_page != nullptr) {
      delete wifi_save_result_page;
      wifi_save_result_page = nullptr;
    }

    if (wifi_sniff_page != nullptr) {
        delete wifi_sniff_page;
        wifi_sniff_page = nullptr;
    }
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
    wifi_sniff_page = new WifiSniffPage(0, 0, 0, gui->get_screen(), gui);
    gui->set_current_page(wifi_sniff_page);
    wifi_sniff_page->display();
    sniff_bssid(gui, &wifiAttack);
}

void init_wifi_networks_gui(vector<WifiNetwork> *networks) {
    delete wifi_scan_page;
    wifi_scan_page = nullptr;
    if (wifi_networks_page == nullptr) /* We can use this page again, so no need
                                          to recreate a new one */
        // wifi_networks_page = new WifiNetworksPage(screen, networks);
        wifi_networks_page =
            new WifiNetworksPage(0, 0, 0, gui->get_screen(), gui, networks);
    wifi_networks_page->display();
    gui->set_current_page(wifi_networks_page);
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
            new WifiScanSaveResultPage(0, 0, 0, gui->get_screen(), gui);
        wifi_save_result_page->display(empty);
        gui->set_current_page(wifi_save_result_page);
        return;
    }
}

/// @brief Destroy WiFI scan result page
void destroy_wifi_scan_result() {
    delete wifi_save_result_page;
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
    delete wifi_page;
    wifi_page = nullptr;
    wifi_sniff_page = new WifiSniffPage(0, 0, 0, gui->get_screen(), gui);
    wifi_sniff_page->display();
}

void display_wifi_scan_result() {
    show_wifi_scan_result_dialog(wifiAttack.get_networks().size() == 0);
}

/// @brief Update sniffed packets in WiFi sniffer page
/// @param count Number of sniffed packets
void update_packets_count(int count) {
    wifi_sniff_page->update_packet_count(count);
}
void init_wifi_navigation(Gui *_gui) { gui = _gui; }
