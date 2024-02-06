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

#include <map>
#include <Arduino.h>
#include "i18n.hpp"
#include "i18n/main_page_keys.h"
#include "i18n/wifi/wifi_submenu_keys.h"
#include "i18n/wifi/wifi_network_details_keys.h"
#include "i18n/wifi/wifi_scan_keys.h"
#include "i18n/wifi/wifi_sniff_keys.h"
#include "i18n/BLE/BLE_submenu_keys.h"
#include "i18n/BLE/ble_scan_keys.h"
#include "i18n/BLE/ble_spam_keys.h"
#include "i18n/network_attacks/net_attacks_main_page.h"
#include "i18n/network_attacks/evilportal_keys.h"
#include "i18n/network_attacks/dhcpglutton_keys.h"

std::map<const char *, const char *> *english_words;

void init_english_dict() {
    english_words = new std::map<const char *, const char *>();
    // Home
    english_words->insert({WIFI_HOME_KEY, "Wi-Fi"});
    english_words->insert({BLE_HOME_KEY, "BLE"});
    english_words->insert({BADUSB_HOME_KEY, "BadUSB"});
    english_words->insert({SUBGHZ_HOME_KEY, "SubGHz"});
    english_words->insert({NFC_HOME_KEY, "NFC"});
    english_words->insert({IR_HOME_KEY, "IR"});
    english_words->insert({NET_ATTACKS_HOME_KEY, "NetAt."});
    english_words->insert({SETTINGS_HOME_KEY, "Sett."});
    english_words->insert({VERSION_KEY, "Version "});
    // Home

    // WiFi
    english_words->insert({WIFI_SCAN_KEY, "Scan"});
    english_words->insert({WIFI_SNIFF_KEY, "Sniff"});
    english_words->insert({WIFI_SCANNING_KEY, "Scanning Wi-Fi network..."});
    english_words->insert({WIFI_AUTH_KEY, "Auth: "});
    english_words->insert({WIFI_SSID_KEY, "SSID: "});
    english_words->insert({WIFI_SSID_HIDDEN_KEY, "SSID Hidden"});
    english_words->insert({WIFI_BSSID_KEY, "BSSID: "});
    english_words->insert({WIFI_RSSI_KEY, "RSSI: "});
    english_words->insert({WIFI_CH_KEY, "CH: "});
    english_words->insert({WIFI_SCAN_SAVE_SD_KEY, "Save scan to SD"});
    english_words->insert({WIFI_SCAN_SNIFF_FILTER_KEY, "Sniff network packets"});
    english_words->insert({WIFI_SCAN_GO_BACK_KEY, "Go back to selection"});
    english_words->insert({WIFI_SCAN_EXIT_KEY, "Exit"});
    english_words->insert({WIFI_SNIFFING_INFO_KEY, "Sniffing packets..."});
    english_words->insert({WIFI_SNIFFING_SNIFFED_KEY, "Sniffed packets: "});
    english_words->insert({WIFI_SNIFFING_SAVE_KEY, "Save"});
    // WiFi

#ifndef CONFIG_IDF_TARGET_ESP32S2	// ESP32S2 doesn't support BLE
    english_words->insert({BLE_SCAN_KEY, "Scan"});
    english_words->insert({BLE_SNIFF_KEY, "Sniff"});
    english_words->insert({BLE_SCANNING_KEY, "Scanning BLE devices..."});
    english_words->insert({BLE_SPAM_PROGRESS_KEY, "Spam attack in progress..."});
    english_words->insert({BLE_SPAM_STOP_KEY, "Stop spam"});
#endif

    // Net attacks
    english_words->insert({EVILPORTAL_KEY, "EvilPortal"});
    english_words->insert({DHCP_GLUTTON_KEY, "DHCPGlutton"});
    english_words->insert({RUNNING_EVILPORTAL_KEY, "Running EvilPortal..."});
    english_words->insert({EVILPORTAL_IP_KEY, "EvilPortal IP: "});
    english_words->insert({EVILPORTAL_CAPTURED_REQUESTS_KEY, "Captured requests: "});
    english_words->insert({RUNNING_DHCPGLUTTON_KEY, "Running DHCP Starvation..."});
    english_words->insert({CREATED_DHCPGLUTTON_CLIENTS_KEY, "Created clients: "});
    // Net attacks
}
