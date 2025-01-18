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

#include "WifiNetworksPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/wifi/wifi_network_details_keys.h"
#include "gui.hpp"

WifiNetworksPage::~WifiNetworksPage() {
  delete ssid;
  delete rssi;
  delete bssid;
  delete ch;
  delete auth;
}

void WifiNetworksPage::set_network() {
  if (networks->size() == 0) {
    return;
  }
  if (networks->at(current_network).get_ssid() != "")
    current_ssid = String(english_words->at(WIFI_SSID_KEY)) +
                   networks->at(current_network).get_ssid();
  else
    current_ssid = String(english_words->at(WIFI_SSID_KEY)) +
                   String(english_words->at(WIFI_SSID_HIDDEN_KEY));
  current_rssi = String(english_words->at(WIFI_RSSI_KEY)) +
                 String(networks->at(current_network).get_rssi());
  current_ch = String(english_words->at(WIFI_CH_KEY)) +
               String(networks->at(current_network).get_channel());
  current_bssid = String(english_words->at(WIFI_BSSID_KEY)) +
                  mac_to_string(networks->at(current_network).get_bssid());
  set_auth();
}

void WifiNetworksPage::next_network() {
  current_network++;
  set_network();
  display();
}

void WifiNetworksPage::previous_network() {
  current_network--;
  set_network();
  display();
}

void WifiNetworksPage::left() {
  if (get_current_network_index() == 0) return;
  screen->reset();
  previous_network();
  return;
}

void WifiNetworksPage::right() {
  if (get_current_network_index() == (get_total_network() - 1)) return;
  screen->reset();
  next_network();
}

void WifiNetworksPage::display() {
  if (!displayed) {
    grid = new Grid(screen, 5, 1);
    grid->set_y_spacing(10);
    ssid = new Text(screen, ST77XX_WHITE, current_ssid);
    rssi = new Text(screen, ST77XX_WHITE, current_rssi);
    bssid = new Text(screen, ST77XX_WHITE, current_bssid);
    ch = new Text(screen, ST77XX_WHITE, current_ch);
    auth = new Text(screen, ST77XX_WHITE, current_auth);
    grid->add(ssid);
    grid->add(bssid);
    grid->add(rssi);
    grid->add(ch);
    grid->add(auth);
    grid->display();
    displayed = true;
  } else {
    ssid->set_text(current_ssid);
    bssid->set_text(current_bssid);
    rssi->set_text(current_rssi);
    ch->set_text(current_ch);
    auth->set_text(current_auth);
  }
}

void WifiNetworksPage::set_auth() {
  WifiNetwork network = networks->at(current_network);
  switch (network.get_auth_mode()) {
    case WIFI_AUTH_OPEN:
      current_auth =
          String(english_words->at(WIFI_AUTH_KEY)) + STRING_WIFI_AUTH_OPEN;
      break;
    case WIFI_AUTH_WEP:
      current_auth =
          String(english_words->at(WIFI_AUTH_KEY)) + STRING_WIFI_AUTH_WEP;
      break;
    case WIFI_AUTH_WPA_PSK:
      current_auth =
          String(english_words->at(WIFI_AUTH_KEY)) + STRING_WIFI_AUTH_WPA_PSK;
      break;
    case WIFI_AUTH_WPA2_PSK:
      current_auth =
          String(english_words->at(WIFI_AUTH_KEY)) + STRING_WIFI_AUTH_WPA2_PSK;
      break;
    case WIFI_AUTH_WPA_WPA2_PSK:
      current_auth = String(english_words->at(WIFI_AUTH_KEY)) +
                     STRING_WIFI_AUTH_WPA_WPA2_PSK;
      break;
    case WIFI_AUTH_WPA2_ENTERPRISE:
      current_auth = String(english_words->at(WIFI_AUTH_KEY)) +
                     STRING_WIFI_AUTH_WPA2_ENTERPRISE;
      break;
    case WIFI_AUTH_WPA3_PSK:
      current_auth =
          String(english_words->at(WIFI_AUTH_KEY)) + STRING_WIFI_AUTH_WPA3_PSK;
      break;
    case WIFI_AUTH_WPA2_WPA3_PSK:
      current_auth = String(english_words->at(WIFI_AUTH_KEY)) +
                     STRING_WIFI_AUTH_WPA2_WPA3_PSK;
      break;
    case WIFI_AUTH_WAPI_PSK:
      current_auth =
          String(english_words->at(WIFI_AUTH_KEY)) + STRING_WIFI_AUTH_WAPI_PSK;
      break;
    case WIFI_AUTH_MAX:
      current_auth =
          String(english_words->at(WIFI_AUTH_KEY)) + STRING_WIFI_AUTH_MAX;
      break;
    default:
      break;
  }
}

void WifiNetworksPage::click() {
  show_wifi_scan_result_dialog(networks->empty());
}