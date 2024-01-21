/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or https://capibarazero.github.io/).
 * Copyright (c) 2024 Andrea Canale.
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

#include "GFXForms.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "widgets/RectText.hpp"
#include "pages/wifi/WifiNetworksPage.hpp"
#include "pages/wifi/WifiPage.hpp"
#include "pages/wifi/WifiScanPage.hpp"
#include "pages/wifi/WifiScanSaveResultPage.hpp"
#include "pages/wifi/WifiSniffPage.hpp"
#include "wifi_attack.hpp"

#ifndef GUI_H
#define GUI_H

class Gui {
 private:
  GFXForms *screen;

  // Wi-Fi
  RectText *wifi;
  WifiPage *wifi_page = nullptr;
  WifiScanPage *wifi_scan_page = nullptr;
  WifiNetworksPage *wifi_networks_page = nullptr;
  WifiScanSaveResultPage *wifi_save_result_page = nullptr;
  WifiSniffPage *wifi_sniff_page = nullptr;

  // BLE
#ifndef CONFIG_IDF_TARGET_ESP32S2
  RectText *ble;
#endif
#if defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3)
  RectText *badusb;
#endif
  RectText *SubGhz;
  RectText *NFC;
  RectText *IR;
  RectText *net_attacks;
  RectText *settings;
  Grid *grid;
  int current_position = 0;
  void init_icons();
  void init_text();
  void up_submenu();

  void down_submenu();
  void ok_submenu(void callback());
  void left_scanned_wifi();

 public:
  Gui(GFXForms *_screen) {
    screen = _screen;
  };
  ~Gui(){};
  /// @brief Init main GUI
  void init_gui();
  /// @brief Init WiFi attacks GUI
  void init_wifi_gui();
  /// @brief Init WiFi scan GUI
  void init_wifi_scan_gui();
  /// @brief Init scanned networks selection GUI
  /// @param networks Scanned networks
  void init_wifi_networks_gui(vector<WifiNetwork> *networks);
  /// @brief Change selected display
  /// @param pos GUI element to click
  void set_selected_widget(int pos, bool selected);
  /// @brief Click and element and call a function on click
  /// @param pos GUI element to click
  /// @param callback function to call
  void click_element(int pos, void callback());

  /// @brief Clean the screen(fill black color)
  void reset() {
    screen->reset();
  }

  /// @brief Update WiFi scan progress
  /// @param progress 
  void set_progress(char *progress) {
    wifi_scan_page->update_progress(progress);
  }
  /// @brief Update scanned WiFi channel
  /// @param channel Channel to display in text
  void set_wifi_channel_text(char *channel) {
    wifi_scan_page->set_ch_text(channel);
  }

  /// @brief Generate arrrow-up event and propagate to current page
  void up();

  /// @brief Generate arrrow-down event and propagate to current page
  void down();

  /// @brief Generate arrrow-left event and propagate to current page
  void left();

  /// @brief Generate arrrow-right event and propagate to current page
  void right();

  /// @brief Mock ok event
  void ok(){};

  /// @brief Generate ok event and propagate to current page
  /// @param callback function to call
  void ok(void callback());

  /// @brief Get current grid selected object
  /// @return Selected object position
  int get_current_position() {
    return current_position;
  }


  /// @brief Return if grid is visible or not(sub menu displayed)
  /// @return submenu visible or not
  bool submenu_visible() {
    return grid == nullptr;
  }

/*********************** WIFI GUI FUNCTIONS *************************/
  /// @brief Return if wifi initial sub menu is visible or not
  /// @return wifi sub menu visible or not
  bool get_wifi_sub_menu() {
    return wifi_page != nullptr && grid == nullptr;
  }

  /// @brief Return if WiFi networks selection is visible or not
  /// @return WiFI network selection visible or not
  bool get_wifi_scan_result_visible() {
    return wifi_networks_page != nullptr;
  }

  /// @brief Get selected network in WiFi scan selection
  /// @return selected network in WiFi scan selection
  WifiNetwork get_current_network() { return wifi_networks_page->get_current_network(); }

  /// @brief Create a WiFi scan final dialog(save to SD, sniff BSSID, go back or return)
  void show_wifi_scan_result_dialog();

  /// @brief Get if WiFi scan final dialog is visible or not
  /// @return WiFi scan final dialog visible or not
  bool wifi_scan_save_visible() { return wifi_save_result_page != nullptr; }

  /// @brief Get WiFi scan final dialog selected position
  /// @return WiFi scan final dialog selected position
  int get_selection_index() { return wifi_save_result_page->get_index(); }

  /// @brief Cleanup WiFi GUI stuff
  void wifi_cleanup();

  /// @brief Destroy WiFI scan result page
  void destroy_wifi_scan_result() {
    delete wifi_save_result_page;
    wifi_save_result_page = nullptr;
  }

/*********************** WIFI SNIFFER GUI FUNCTIONS *************************/

  /// @brief Show sniffer page
  void show_wifi_sniff_page();

  /// @brief Return if WiFi sniff page is visible
  /// @return WiFi sniff page visible or not
  bool get_wifi_sniff_menu() {
    return wifi_sniff_page != nullptr;
  }

  /// @brief Update sniffed packets in WiFi sniffer page
  /// @param count Number of sniffed packets
  void update_packets_count(int count) {
    wifi_sniff_page->update_packet_count(count);
  }

  /// @brief Destroy sniff page
  void destroy_wifi_sniff() {
    delete wifi_sniff_page;
    wifi_sniff_page = nullptr;
  }
};

#endif
