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


// Begin SubGHZ
const char *get_var_subghz_frequency_analyzer_freq();

void set_var_subghz_frequency_analyzer_freq(const char *value);

const char *get_var_subghz_frequency_analyzer_rssi();

void set_var_subghz_frequency_analyzer_rssi(const char *value);


const char *get_var_nfc_atqa();
void set_var_nfc_atqa(const char *value);

const char *get_var_nfc_sak();
void set_var_nfc_sak(const char *value);

const char *get_var_nfc_tag_type();
void set_var_nfc_tag_type(const char *value);

const char *get_var_nfc_written_sectors();
void set_var_nfc_written_sectors(const char *value);

const char *get_var_nfc_unwritable_sectors();
void set_var_nfc_unwritable_sectors(const char *value);

const char *get_var_nfc_tried_keys();
void set_var_nfc_tried_keys(const char *value);

const char *get_var_nfc_found_keys();
void set_var_nfc_found_keys(const char *value);

const char *get_var_nfc_sys_code();
void set_var_nfc_sys_code(const char *value);

const char *get_var_nfc_felica_read_sector();
void set_var_nfc_felica_read_sector(const char *value);

const char *get_var_nfc_felica_unreadable_sectors();
void set_var_nfc_felica_unreadable_sectors(const char *value);

const char *get_var_nfc_emv_type();
void set_var_nfc_emv_type(const char *value);

const char *get_var_nfc_emv_card_number();
void set_var_nfc_emv_card_number(const char *value); 

const char *get_var_nfc_emv_card_issue();
void set_var_nfc_emv_card_issue(const char *value);

const char *get_var_nfc_emv_card_expire();
void set_var_nfc_emv_card_expire(const char *value);

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NONE
};

// Native global variables



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/
