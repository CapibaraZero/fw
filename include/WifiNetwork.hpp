/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2023 Andrea Canale.
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

#ifndef WIFINETWORK_H
#define WIFINETWORK_H

#include <WiFi.h>

class WifiNetwork {
 private:
  String ssid;
  int rssi;
  uint8_t *bssid;
  int channel;
  wifi_auth_mode_t auth_mode;

 public:
  WifiNetwork(String _ssid, int _rssi, uint8_t *_bssid, int _channel,
              wifi_auth_mode_t _auth_mode) {
    ssid = _ssid;
    rssi = _rssi;
    bssid = _bssid;
    channel = _channel;
    auth_mode = _auth_mode;
  }
  String get_ssid() { return ssid; }
  int get_rssi() { return rssi; }
  uint8_t *get_bssid() { return bssid; }
  int get_channel() { return channel; }
  wifi_auth_mode_t get_auth_mode() { return auth_mode; }
};

#endif
