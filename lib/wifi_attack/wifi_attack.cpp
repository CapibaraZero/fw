/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2025 Andrea Canale.
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

/* This file contains implementation of wifiAttack class */

#include "wifi_attack.hpp"

#include "../../include/pcap_gen.h"
#include "ArduinoJson.h"
#include "posixsd.hpp"

#define MAX_WIFI_CHANNEL 13  // Max channel that ESP32 will use for scanning
#define CHANGE_CHANNEL_TIME 5000  // Switch channel every 5 seconds
#define PCAP_TYPE String("wifi")
#define SCAN_FILENAME String(String("/wifi/scan_") + millis() + String(".json"))

WifiAttack::WifiAttack(/* args */) {}

WifiAttack::~WifiAttack() {}

void WifiAttack::scan() {
  WiFi.mode(WIFI_OFF); // otherwise Wifi.Scannetworks() fails
  delay(5000);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);
  int n = WiFi.scanNetworks(false, true, false, 300);
  for (int i = 0; i < n; i++) {
    WifiNetwork network = WifiNetwork(WiFi.SSID(i), WiFi.RSSI(i), WiFi.BSSID(i),
                                      WiFi.channel(i), WiFi.encryptionType(i));
    networks.push_back(network);
  }
  WiFi.scanDelete();  // Clean result since we save result in a vector
}

String WifiAttack::scan_to_str() {
  JsonDocument all_networks;

  for (auto network : networks) {
    JsonDocument wifi;
    JsonDocument doc;
    JsonArray json_bssid = doc.to<JsonArray>();
    uint8_t *bssid = network.get_bssid();
    for (size_t i = 0; i < 6; i++) {
      json_bssid.add(bssid[i]);
    }
    wifi["ssid"] = network.get_ssid();
    wifi["rssi"] = network.get_rssi();
    wifi["bssid"] = json_bssid;
    wifi["channel"] = network.get_channel();
    wifi["auth_mode"] = network.get_auth_mode();
    all_networks.add(wifi);
  }
  String json;
  serializeJson(all_networks, json);
  return json;
}

void WifiAttack::save_scan() {
  JsonDocument all_networks;

  for (auto network : networks) {
#ifdef ARDUINO_NANO_ESP32
    Serial.printf("SSID: %s\n", network.get_ssid());
#else
    Serial0.printf("SSID: %s\n", network.get_ssid());
#endif
    JsonDocument wifi;
    JsonDocument doc;
    JsonArray json_bssid = doc.to<JsonArray>();
    uint8_t *bssid = network.get_bssid();
    for (size_t i = 0; i < 6; i++) {
      json_bssid.add(bssid[i]);
    }
    wifi["ssid"] = network.get_ssid();
    wifi["rssi"] = network.get_rssi();
    wifi["bssid"] = json_bssid;
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
    delay(wait_time);  // Wait before changing channel, sniffer will sniff
                       // meanwhile.
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
