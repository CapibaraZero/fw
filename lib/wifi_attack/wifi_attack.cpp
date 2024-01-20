/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or https://capibarazero.github.io/).
 * Copyright (c) 2023 Andrea Canale.
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

#include "wifi_attack.hpp"

#include "../../include/pcap_gen.h"
#include "ArduinoJson.h"
#include "posixsd.hpp"

#define MAX_WIFI_CHANNEL 13       // Max channel that ESP32 will use for scanning
#define CHANGE_CHANNEL_TIME 5000  // Switch channel every 5 seconds
#define PCAP_TYPE String("wifi")
#define SCAN_FILENAME String(String("/wifi/scan_") + millis() + String(".json"))

WifiAttack::WifiAttack(/* args */) {
}

WifiAttack::~WifiAttack() {
  Serial0.println("Destroyed");
}

vector<WifiNetwork> WifiAttack::scan() {
  int n = WiFi.scanNetworks(false, true, false, 1000);
  vector<WifiNetwork> networks_found = vector<WifiNetwork>();
  for (int i = 0; i < n; i++) {
    WifiNetwork network = WifiNetwork(WiFi.SSID(i), WiFi.RSSI(i), WiFi.BSSID(i), WiFi.channel(i), WiFi.encryptionType(i));
    networks_found.push_back(network);
  }

  return networks_found;
}

void WifiAttack::save_scan(vector<WifiNetwork> *networks) {
  DynamicJsonDocument all_networks(2048);

  for (auto network : *networks) {
    Serial0.printf("SSID: %s\n", network.get_ssid());
    DynamicJsonDocument wifi(512);
    wifi["ssid"] = network.get_ssid();
    wifi["rssi"] = network.get_rssi();
    wifi["bssid"] = network.get_bssid();
    wifi["channel"] = network.get_channel();
    wifi["auth_mode"] = network.get_auth_mode();
    all_networks.add(wifi);
  }
  File file = open(SCAN_FILENAME, "w");
  serializeJson(all_networks, file);
  file.close();
}

void WifiAttack::rotate_all_channels(int max_ch, int wait_time) {
  for (int i = 1; i < max_ch; i++) {
    esp_wifi_set_channel(i, (wifi_second_chan_t)NULL);
    delay(wait_time);  // Wait before changing channel, sniffer will sniff meanwhile.
  }
}

void WifiAttack::sniff(int delay, FS sd) {
  sniffer = new WifiSniffer(PCAP_FILE(PCAP_TYPE).c_str(), sd);
  for (;;) {
    rotate_all_channels(MAX_WIFI_CHANNEL, delay);
  }
}

void WifiAttack::sniff(int max_ch, int delay, FS sd) {
  sniffer = new WifiSniffer(PCAP_FILE(PCAP_TYPE).c_str(), sd);
  rotate_all_channels(max_ch, delay);
}

void WifiAttack::sniff_channel(int channel, int time, FS sd) {
  sniffer = new WifiSniffer(PCAP_FILE(PCAP_TYPE).c_str(), sd, channel);
}

void WifiAttack::sniff_bssid(uint8_t *bssid, int ch, FS sd) {
  sniffer = new WifiSniffer(PCAP_FILE(PCAP_TYPE).c_str(), sd, bssid, ch);
}