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

#include <string>
#include "vars.h"

// BEGIN WIFI

std::string wifi_scan_current_progress = "Progress: 0%";

extern "C" const char *get_var_wifi_scan_current_progress() {
    return wifi_scan_current_progress.c_str();
}

extern "C" void set_var_wifi_scan_current_progress(const char *value) {
    wifi_scan_current_progress = value;
}

std::string wifi_scan_current_channel = "Channel: 1";

extern "C" const char *get_var_wifi_scan_current_channel() {
    return wifi_scan_current_channel.c_str();
}

extern "C" void set_var_wifi_scan_current_channel(const char *value) {
    wifi_scan_current_channel = value;
}

std::string wifi_scan_info = "Initializing WiFi stack...";

extern "C" const char *get_var_wifi_scan_info() {
    return wifi_scan_info.c_str();
}

extern "C" void set_var_wifi_scan_info(const char *value) {
    wifi_scan_info = value;
}

std::string wifi_current_ssid;

extern "C" const char *get_var_wifi_current_ssid() {
    return wifi_current_ssid.c_str();
}

extern "C" void set_var_wifi_current_ssid(const char *value) {
    wifi_current_ssid = value;
}

std::string wifi_current_rssi;

extern "C" const char *get_var_wifi_current_rssi() {
    return wifi_current_rssi.c_str();
}

extern "C" void set_var_wifi_current_rssi(const char *value) {
    wifi_current_rssi = value;
}

std::string wifi_current_channel;

extern "C" const char *get_var_wifi_current_channel() {
    return wifi_current_channel.c_str();
}

extern "C" void set_var_wifi_current_channel(const char *value) {
    wifi_current_channel = value;
}

std::string wifi_current_bssid;

extern "C" const char *get_var_wifi_current_bssid() {
    return wifi_current_bssid.c_str();
}

extern "C" void set_var_wifi_current_bssid(const char *value) {
    wifi_current_bssid = value;
}

std::string captured_packets = "Captured packets: ";

extern "C" const char *get_var_captured_packets() {
    return captured_packets.c_str();
}

extern "C" void set_var_captured_packets(const char *value) {
    captured_packets = value;
}

std::string evilportal_ip;

extern "C" const char *get_var_evilportal_ip() {
    return evilportal_ip.c_str();
}

extern "C" void set_var_evilportal_ip(const char *value) {
    evilportal_ip = value;
}

std::string evilportal_captured_requests;

extern "C" const char *get_var_evilportal_captured_requests() {
    return evilportal_captured_requests.c_str();
}

extern "C" void set_var_evilportal_captured_requests(const char *value) {
    evilportal_captured_requests = value;
}

std::string dhcpglutton_generated_client;

extern "C" const char *get_var_dhcpglutton_generated_client() {
    return dhcpglutton_generated_client.c_str();
}

extern "C" void set_var_dhcpglutton_generated_client(const char *value) {
    dhcpglutton_generated_client = value;
}
// END WIFI

// BEGIN SubGHZ

std::string subghz_frequency_analyzer_freq = "Frequency: ";

extern "C" const char *get_var_subghz_frequency_analyzer_freq() {
    return subghz_frequency_analyzer_freq.c_str();
}

extern "C" void set_var_subghz_frequency_analyzer_freq(const char *value) {
    subghz_frequency_analyzer_freq = value;
}

std::string subghz_frequency_analyzer_rssi = "RSSI: ";

extern "C" const char *get_var_subghz_frequency_analyzer_rssi() {
    return subghz_frequency_analyzer_rssi.c_str();
}

extern "C" void set_var_subghz_frequency_analyzer_rssi(const char *value) {
    subghz_frequency_analyzer_rssi = value;
}

std::string nfc_atqa;

extern "C" const char *get_var_nfc_atqa() {
    return nfc_atqa.c_str();
}

extern "C" void set_var_nfc_atqa(const char *value) {
    nfc_atqa = value;
}

std::string nfc_sak;

extern "C" const char *get_var_nfc_sak() {
    return nfc_sak.c_str();
}

extern "C" void set_var_nfc_sak(const char *value) {
    nfc_sak = value;
}

std::string nfc_tag_type;

extern "C" const char *get_var_nfc_tag_type() {
    return nfc_tag_type.c_str();
}

extern "C" void set_var_nfc_tag_type(const char *value) {
    nfc_tag_type = value;
}

std::string nfc_written_sectors;

extern "C" const char *get_var_nfc_written_sectors() {
    return nfc_written_sectors.c_str();
}

extern "C" void set_var_nfc_written_sectors(const char *value) {
    nfc_written_sectors = value;
}

std::string nfc_unwritable_sectors;

extern "C" const char *get_var_nfc_unwritable_sectors() {
    return nfc_unwritable_sectors.c_str();
}

extern "C" void set_var_nfc_unwritable_sectors(const char *value) {
    nfc_unwritable_sectors = value;
}

std::string nfc_tried_keys;

extern "C" const char *get_var_nfc_tried_keys() {
    return nfc_tried_keys.c_str();
}

extern "C" void set_var_nfc_tried_keys(const char *value) {
    nfc_tried_keys = value;
}

std::string nfc_found_keys;

extern "C" const char *get_var_nfc_found_keys() {
    return nfc_found_keys.c_str();
}

extern "C" void set_var_nfc_found_keys(const char *value) {
    nfc_found_keys = value;
}

std::string nfc_sys_code;

extern "C" const char *get_var_nfc_sys_code() {
    return nfc_sys_code.c_str();
}

extern "C" void set_var_nfc_sys_code(const char *value) {
    nfc_sys_code = value;
}

std::string nfc_felica_read_sector;

extern "C" const char *get_var_nfc_felica_read_sector() {
    return nfc_felica_read_sector.c_str();
}

extern "C" void set_var_nfc_felica_read_sector(const char *value) {
    nfc_felica_read_sector = value;
}

std::string nfc_felica_unreadable_sectors;

extern "C" const char *get_var_nfc_felica_unreadable_sectors() {
    return nfc_felica_unreadable_sectors.c_str();
}

extern "C" void set_var_nfc_felica_unreadable_sectors(const char *value) {
    nfc_felica_unreadable_sectors = value;
}

std::string nfc_emv_type = "Reading EMV...";

extern "C" const char *get_var_nfc_emv_type() {
    return nfc_emv_type.c_str();
}

extern "C" void set_var_nfc_emv_type(const char *value) {
    nfc_emv_type = value;
}

std::string nfc_emv_card_number;

extern "C" const char *get_var_nfc_emv_card_number() {
    return nfc_emv_card_number.c_str();
}

extern "C" void set_var_nfc_emv_card_number(const char *value) {
    nfc_emv_card_number = value;
}

std::string nfc_emv_card_issue;

extern "C" const char *get_var_nfc_emv_card_issue() {
    return nfc_emv_card_issue.c_str();
}

extern "C" void set_var_nfc_emv_card_issue(const char *value) {
    nfc_emv_card_issue = value;
}

std::string nfc_emv_card_expire;

extern "C" const char *get_var_nfc_emv_card_expire() {
    return nfc_emv_card_expire.c_str();
}

extern "C" void set_var_nfc_emv_card_expire(const char *value) {
    nfc_emv_card_expire = value;
}