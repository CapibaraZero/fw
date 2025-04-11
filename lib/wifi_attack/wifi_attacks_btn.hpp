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

// This file contains functions that starts wifiAttack on button click

#include "wifi_attack.hpp"

void scan_wifi(WifiAttack *wifiAttack);
void sniff_wifi(WifiAttack *wifiAttack);
void stop_wifi_sniffer_updater();
void sniff_bssid(WifiAttack *wifiAttack, WifiNetwork *network);