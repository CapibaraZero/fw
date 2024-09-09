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

#ifndef BLE_NAVIGATION_H
#define BLE_NAVIGATION_H

#include "gui.hpp"

void goto_ble_gui();
void goto_ble_sniff_gui();
void goto_applejuice();
void goto_samsung_spam();
void goto_swift_spam();
void goto_fastpair_spam();
// void set_ble_adv_devices_text(int adv_devices);
// void set_ble_progress(char *progress);
void update_ble_packets_count(int count);
void ble_goto_home();
void init_ble_navigation(Gui *_gui);
void stop_ble_sniffer();
void stop_applejuice();
void stop_samsung_ble_spam();
void stop_swift_pair_spam();
void handle_ble_spam_stop();

#endif
