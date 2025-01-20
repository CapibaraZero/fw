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

#ifndef WIFI_NETWORKS_PAGE
#define WIFI_NETWORKS_PAGE

#include "../../navigation/wifi/wifi_navigation.hpp"
#include "../Page.hpp"
#include "Grid.hpp"
#include "Text.hpp"
#include "wifi_attack.hpp"

/* From esp_wifi_types.h */
#define STRING_WIFI_AUTH_OPEN "OPEN"
#define STRING_WIFI_AUTH_WEP "WEP"
#define STRING_WIFI_AUTH_WPA_PSK "WPA-PSK"
#define STRING_WIFI_AUTH_WPA2_PSK "WPA2-PSK"
#define STRING_WIFI_AUTH_WPA_WPA2_PSK "WPA-WPA2-PSK"
#define STRING_WIFI_AUTH_WPA2_ENTERPRISE "WPA2-ENTERPRISE"
#define STRING_WIFI_AUTH_WPA3_PSK "WPA3-PSK"
#define STRING_WIFI_AUTH_WPA2_WPA3_PSK "WPA2-WPA3-PSK"
#define STRING_WIFI_AUTH_WAPI_PSK "WAPI-PSK"
#define STRING_WIFI_AUTH_MAX "Unsupported"

class WifiNetworksPage : public Page {
 private:
  Text *ssid;
  Text *rssi;
  Text *bssid;
  Text *ch;
  Text *auth;
  vector<WifiNetwork> *networks;
  String current_ssid = "No network found.";
  String current_rssi = "";
  String current_ch = "";
  String current_auth = "";
  String current_bssid = "";
  bool displayed = false;
  int current_network = 0;
  void set_network();
  void set_auth();
  String mac_to_string(uint8_t *mac) {
    String mac_str = "";
    for (size_t i = 0; i < 6; i++) {
      mac_str += (String(mac[i], HEX) + ":");
    }
    mac_str[17] = '\0';
    return mac_str;
  }

 public:
  WifiNetworksPage(uint8_t _position_limit, uint8_t _lower_limit,
                   uint8_t _position_increment, GFXForms *screen,
                   vector<WifiNetwork> *_networks)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
    networks = _networks;
    set_network();
  };
  ~WifiNetworksPage();
  void next_network();
  void previous_network();
  void display();
  WifiNetwork get_current_network() { return networks->at(current_network); };
  int get_current_network_index() { return current_network; };
  int get_total_network() { return networks->size(); };
  void left();
  void right();
  void click();
};

#endif