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

#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations
const char *get_var_wifi_scan_current_progress();

void set_var_wifi_scan_current_progress(const char *value);

const char *get_var_wifi_scan_current_channel();

void set_var_wifi_scan_current_channel(const char *value);

const char *get_var_wifi_scan_info();

void set_var_wifi_scan_info(const char *value);

const char *get_var_wifi_current_ssid();

void set_var_wifi_current_ssid(const char *value);

const char *get_var_wifi_current_rssi();

void set_var_wifi_current_rssi(const char *value);

const char *get_var_wifi_current_channel();

void set_var_wifi_current_channel(const char *value);

const char *get_var_wifi_current_bssid();

void set_var_wifi_current_bssid(const char *value);

const char *get_var_captured_packets();

void set_var_captured_packets(const char *value);

const char *get_var_evilportal_ip();

void set_var_evilportal_ip(const char *value);

const char *get_var_evilportal_captured_requests();

void set_var_evilportal_captured_requests(const char *value);

const char *get_var_dhcpglutton_generated_client();

void set_var_dhcpglutton_generated_client(const char *value);
// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NONE
};

// Native global variables



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/