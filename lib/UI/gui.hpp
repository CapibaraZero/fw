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

#include "GFXForms.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "pages/BLE/BLEPage.hpp"
#include "pages/BLE/BLEScanPage.hpp"
#include "pages/BLE/BLESniffPage.hpp"
#include "pages/BLE/BLESpamPage.hpp"
#include "pages/BadUSB/BadUSBPayloadBrowserPage.hpp"
#include "pages/NFC/FeliCaPages/NFCFelicaPollingResultPage.hpp"
#include "pages/NFC/NFCBruteforceTagPage.hpp"
#include "pages/NFC/NFCDumpResultPage.hpp"
#include "pages/NFC/NFCFormatResultPage.hpp"
#include "pages/NFC/NFCMainPage.hpp"
#include "pages/NFC/NFCPollingResultPage.hpp"
#include "pages/NFC/NFCPollingWaitingPage.hpp"
#include "pages/NFC/NFCWriteResultPage.hpp"
#include "pages/network_attacks/DHCPGluttonPage.hpp"
#include "pages/network_attacks/EvilPortalPage.hpp"
#include "pages/network_attacks/NetworkAttacksPage.hpp"
#include "pages/network_attacks/ARPoisonerPage.hpp"
#include "pages/wifi/WifiNetworksPage.hpp"
#include "pages/wifi/WifiPage.hpp"
#include "pages/wifi/WifiScanPage.hpp"
#include "pages/wifi/WifiScanSaveResultPage.hpp"
#include "pages/wifi/WifiSniffPage.hpp"
#include "widgets/RectText.hpp"
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
  BLEPage *ble_page = nullptr;
  BLEScanPage *ble_scan_page = nullptr;
  BLESniffPage *ble_sniff_page = nullptr;
  BLESpamPage *ble_spam_page = nullptr;
#endif
#if defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3)
  RectText *badusb;
  BadUSBPayloadBrowserPage *badusb_payload_browser_page = nullptr;
#endif
  RectText *SubGhz;
  // NFC
  RectText *NFC;
  NFCMainPage *nfc_main_page = nullptr;
  NFCPollingWaitingPage *nfc_polling_waiting_page = nullptr;
  NFCPollingResultPage *nfc_polling_result_page = nullptr;
  NFCDumpResultPage *nfc_dump_result_page = nullptr;
  NFCWriteResultPage *nfc_write_result_page = nullptr;
  NFCFormatResultPage *nfc_format_result_page = nullptr;
  NFCBruteforceTagPage *nfc_bruteforce_tag_page = nullptr;
  NFCFelicaPollingResultPage *nfc_felica_polling_result_page = nullptr;
  // NFC
  RectText *IR;
  // Network attacks
  RectText *net_attacks;
  NetworkAttacksPage *net_attacks_page = nullptr;
  DHCPGluttonPage *dhcp_glutton_page = nullptr;
  EvilPortalPage *evilportal_page = nullptr;
  ARPoisonerPage *arpoisoner_page = nullptr;
  // Network attacks
  RectText *settings;
  Grid *grid = nullptr;
  bool grid_visible = false;
  int current_position = 0;
  int position_limit = 7;  // Maximum number of widgets in the page
  int lower_limit = 0;     // Start position
  int position_increment =
      4;  // Maximum increment of position by a single button
  void init_icons();
  void init_text();
  void up_submenu();

  void down_submenu();
  void ok_submenu(void callback());
  void left_scanned_wifi();

 public:
  Gui(GFXForms *_screen) { screen = _screen; };
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
  void reset() { screen->reset(); }

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
  void ok() {};

  /// @brief Generate ok event and propagate to current page
  /// @param callback function to call
  void ok(void callback());

  /// @brief Get current grid selected object
  /// @return Selected object position
  int get_current_position() { return current_position; }

  void set_current_position(int pos) { current_position = pos; }

  void set_position_limit(int limit) { position_limit = limit; }

  /// @brief Return if grid is visible or not(sub menu displayed)
  /// @return submenu visible or not
  bool submenu_visible() { return !grid_visible; }

  /*********************** WIFI GUI FUNCTIONS *************************/
  /// @brief Return if wifi initial sub menu is visible or not
  /// @return wifi sub menu visible or not
  bool get_wifi_sub_menu() { return wifi_page != nullptr && submenu_visible(); }

  /// @brief Return if WiFi networks selection is visible or not
  /// @return WiFI network selection visible or not
  bool get_wifi_scan_result_visible() { return wifi_networks_page != nullptr; }

  /// @brief Get selected network in WiFi scan selection
  /// @return selected network in WiFi scan selection
  WifiNetwork get_current_network() {
    return wifi_networks_page->get_current_network();
  }

  /// @brief Create a WiFi scan final dialog(save to SD, sniff BSSID, go back or
  /// return)
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
  bool get_wifi_sniff_menu() { return wifi_sniff_page != nullptr; }

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

  /*********************** BLE GUI FUNCTIONS *************************/

  void init_ble_gui();
  void destroy_ble_gui() {
    delete ble_page;
    ble_page = nullptr;
  }
  bool get_ble_sub_menu() { return ble_page != nullptr; }
  void init_ble_scan_gui();
  void set_ble_adv_devices_text(int adv_devices) {
    ble_scan_page->set_adv_devices_text(String(adv_devices).c_str());
  }
  void set_ble_progress(char *progress) {
    ble_scan_page->update_progress(progress);
  };
  void init_ble_sniff_gui();
  void update_ble_packets_count(int count) {
    ble_sniff_page->update_packet_count(count);
  };
  bool ble_sniff_visible() { return ble_sniff_page != nullptr; };
  void init_ble_spam_gui();
  bool ble_spam_visible() { return ble_spam_page != nullptr; };
  void destroy_ble_sniff_gui() {
    delete ble_sniff_page;
    ble_sniff_page = nullptr;
  }
  void destroy_ble_spam_gui() {
    delete ble_spam_page;
    ble_spam_page = nullptr;
  }

  /****************** NET ATTACKS GUI FUNCTIONS *********************/

  void init_network_attacks_gui();
  void destroy_network_attacks_gui() {
    delete net_attacks_page;
    net_attacks_page = nullptr;
  }
  bool network_attacks_submenu_visible() {
    return net_attacks_page != nullptr;
  };

  /**************** DHCP STARVATION GUI FUNCTIONS ********************/

  void init_dhcp_glutton_gui();
  bool dhcp_glutton_visible() { return dhcp_glutton_page != nullptr; };
  void set_dhcp_glutton_clients(int client);
  void destroy_dhcp_glutton_gui() {
    delete dhcp_glutton_page;
    dhcp_glutton_page = nullptr;
  }

  /****************** EVILPORTAL GUI FUNCTIONS *********************/

  void init_evilportal_gui();
  bool evilportal_page_visible() { return evilportal_page != nullptr; };
  void destroy_evilportal_gui() {
    delete evilportal_page;
    evilportal_page = nullptr;
  };
  void set_evilportal_requests(int req);
  void set_evilportal_ip(String ip);


  /******************** ARP Poisoner FUNCTIONS ************************/
  void init_arp_poisoner_gui();
  bool arp_poisoner_page_visible() { return arpoisoner_page != nullptr; };
  void destroy_arp_poisoner_gui() {
    delete arpoisoner_page;
    arpoisoner_page = nullptr;
  }
  /******************** BadUSB FUNCTIONS ************************/

  void init_badusb_browser_gui(std::list<std::string> *files);
  bool badusb_browser_visible() {
    return badusb_payload_browser_page != nullptr;
  };
  void destroy_badusb_browser_gui() {
    delete badusb_payload_browser_page;
    badusb_payload_browser_page = nullptr;
  }

  /******************** NFC GUI FUNCTIONS ************************/
  void init_nfc_gui();
  bool nfc_page_visible() { return nfc_main_page != nullptr; };
  void init_nfc_polling_waiting_gui();
  void destroy_nfc_polling_gui() {
    delete nfc_polling_result_page;
    nfc_polling_result_page = nullptr;
  }
  bool nfc_polling_waiting_page_visible() {
    return nfc_polling_waiting_page != nullptr;
  };
  void init_nfc_polling_result_gui(uint8_t *uid, uint8_t length);
  bool nfc_polling_result_page_visible() {
    return nfc_polling_result_page != nullptr;
  };
  void init_nfc_dump_result_gui();
  void destroy_nfc_dump_result_gui() {
    delete nfc_dump_result_page;
    nfc_dump_result_page = nullptr;
  };
  void return_to_nfc_polling_gui();
  bool nfc_dump_result_page_visible() {
    return nfc_dump_result_page != nullptr;
  };
  void set_dumped_sectors(int sectors) {
    nfc_dump_result_page->set_dumped(sectors);
  };
  void set_unreadable_sectors(int sectors) {
    nfc_dump_result_page->set_unreadable(sectors);
  };
  void set_unauthenticated_sectors(int sectors) {
    nfc_dump_result_page->set_unauthenticated(sectors);
  };
  void init_nfc_write_result_gui();
  void set_unwritable_sectors(uint8_t tot, uint8_t sectors) {
    nfc_write_result_page->set_wrote_sectors(tot - sectors);
    nfc_write_result_page->set_unwritable_sectors(sectors);
  };
  void init_nfc_format_result_gui();
  void set_unformatted_sectors(uint8_t tot, uint8_t unformatted) {
    nfc_format_result_page->set_formatted(tot - unformatted);
    nfc_format_result_page->set_unauthenticated(unformatted);
  }
  void destroy_nfc_format_result_gui() {
    delete nfc_format_result_page;
    nfc_format_result_page = nullptr;
  };
  bool nfc_format_page_visible() { return nfc_format_result_page != nullptr; };
  void nfc_cleanup();
  void init_nfc_bruteforce_gui();
  void destroy_nfc_bruteforce_gui() {
    delete nfc_bruteforce_tag_page;
    nfc_bruteforce_tag_page = nullptr;
  }
  void nfc_bruteforce_found_key(bool status) {
    nfc_bruteforce_tag_page->set_found_key(status);
  };
  void nfc_bruteforce_set_tried_key(uint8_t attemps) {
    nfc_bruteforce_tag_page->update_tried_keys(attemps);
  };
  bool nfc_bruteforce_page_visible() {
    return nfc_bruteforce_tag_page != nullptr;
  };
  void init_nfc_felica_polling_result_gui(uint8_t *idm, uint8_t *pmm,
                                          uint16_t sys_code);
  bool nfc_felica_polling_result_page_visible() {
    return nfc_felica_polling_result_page != nullptr;
  };
};

#endif
