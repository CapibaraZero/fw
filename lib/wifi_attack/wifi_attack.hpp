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

/* This file contains definitions of wifiAttack class */

#ifndef WIFIATTACK_H
#define WIFIATTACK_H

#include <vector>

#include "../../include/WifiNetwork.hpp"
#include "FS.h"
#include "wifi_sniffer.hpp"

using namespace std;

class WifiAttack {
 private:
  WifiSniffer *sniffer;
  void rotate_all_channels(int max_ch, int wait_time);
  vector<WifiNetwork> networks;

 public:
  WifiAttack(/* args */);
  ~WifiAttack();

  /// @brief Scan all the WiFi environments
  /// @return A list of all network found
  void scan();

  /// @brief Return scan result to JSON string
  /// @return JSON string with WiFi scan result
  String scan_to_str();

  /// @brief Save WiFI scan result to JSON in SD
  /// @param networks WiFi scan result
  void save_scan();

  /// @brief Sniff all the WiFi environment and save it to SD
  /// @param delay Time before switch to another channel
  /// @param inf Sniff all the time
  void sniff(int delay, FS sd);

  /// @brief Sniff packets and filter selected BSSID
  /// @param bssid BSSID of network to sniff
  /// @param ch Channel of network to sniff
  /// @param sd SD object
  void sniff_bssid(uint8_t *bssid, int ch, FS sd);

  /// @brief Stop sniffer
  void stop_sniff() {
    delete sniffer;
    sniffer = nullptr;
  };

  /// @brief Return if sniffer is running or not
  /// @return Sniffer status
  bool sniffer_running() { return sniffer != nullptr; };

  /// @brief Get total sniffed packets
  /// @return all packets sniffed, since sniffer started
  int get_sniffed_packets() { return sniffer->get_sniffed_packets(); }

  /// @brief Sniff a specific WiFi channel range and save it to SD
  /// @param max_ch Maximium channel that it will scan
  /// @param delay Time before switch to another channel
  /// @param inf Sniff all the time
  void sniff(int max_ch, int delay, FS sd);

  /// @brief Sniff a specific WiFi channel
  /// @param channel WiFi channel to sniff
  /// @param time Time before finish scan. Not used in case of inf==true
  /// @param inf Sniff all the time
  void sniff_channel(int channel, int time, FS sd);

  /// @brief Get scanned network. Invoke this when scan is not running
  /// @return Get all the networks scanned
  vector<WifiNetwork> get_networks() { return networks; };
  /// @brief Clean the networks scanned. Call this when you want to do more than
  /// one scan
  void clean_networks() { networks.clear(); };
};

#endif