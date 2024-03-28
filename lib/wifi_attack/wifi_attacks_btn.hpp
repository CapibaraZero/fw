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

// This file contains functions that starts wifiAttack on button click

#include "gui.hpp"
#include "wifi_attack.hpp"

void scan_wifi(Gui *gui, WifiAttack *wifiAttack);
void sniff_wifi(Gui *gui, WifiAttack *wifiAttack);
void stop_wifi_sniffer_updater();
void sniff_bssid(Gui *gui, WifiAttack *wifiAttack);
void return_to_net_list(Gui *gui);