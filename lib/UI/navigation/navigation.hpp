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

#ifndef NAVIGATION_H
#define NAVIGATION_H

void set_selected_listener(void *pv);
void init_main_gui();
void init_wifi_ui();

void init_ble_ui();

void init_badusb_ui();

void init_subghz_ui();

void init_nfc_ui();

void init_ir_ui();

void init_settings_ui();

void init_scripts_ui();
#endif
