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

std::string ir_protocol = "Waiting for signal...";

extern "C" const char *get_var_ir_protocol() {
    return ir_protocol.c_str();
}

extern "C" void set_var_ir_protocol(const char *value) {
    ir_protocol = value;
}

std::string ir_addr;

extern "C" const char *get_var_ir_addr() {
    return ir_addr.c_str();
}

extern "C" void set_var_ir_addr(const char *value) {
    ir_addr = value;
}

std::string ir_cmd;

extern "C" const char *get_var_ir_cmd() {
    return ir_cmd.c_str();
}

extern "C" void set_var_ir_cmd(const char *value) {
    ir_cmd = value;
}

std::string ir_len;

extern "C" const char *get_var_ir_len() {
    return ir_len.c_str();
}

extern "C" void set_var_ir_len(const char *value) {
    ir_len = value;
}

bool ir_retry = true;   // Hide retry btn

extern "C" bool get_var_ir_retry() {
    return ir_retry;
}

extern "C" void set_var_ir_retry(bool value) {
    ir_retry = value;
}

bool ir_save = true;    // Hide retry btn

extern "C" bool get_var_ir_save() {
    return ir_save;
}

extern "C" void set_var_ir_save(bool value) {
    ir_save = value;
}

std::string ir_emulate_progress;

extern "C" const char *get_var_ir_emulate_progress() {
    return ir_emulate_progress.c_str();
}

extern "C" void set_var_ir_emulate_progress(const char *value) {
    ir_emulate_progress = value;
}

std::string sw_version;

extern "C" const char *get_var_sw_version() {
    return sw_version.c_str();
}

extern "C" void set_var_sw_version(const char *value) {
    sw_version = value;
}

std::string board;

extern "C" const char *get_var_board() {
    return board.c_str();
}

extern "C" void set_var_board(const char *value) {
    board = value;
}

std::string heap_usage;

extern "C" const char *get_var_heap_usage() {
    return heap_usage.c_str();
}

extern "C" void set_var_heap_usage(const char *value) {
    heap_usage = value;
}


std::string chip_revision;

extern "C" const char *get_var_chip_revision() {
    return chip_revision.c_str();
}

extern "C" void set_var_chip_revision(const char *value) {
    chip_revision = value;
}

std::string sd_card_type;

extern "C" const char *get_var_sd_card_type() {
    return sd_card_type.c_str();
}

extern "C" void set_var_sd_card_type(const char *value) {
    sd_card_type = value;
}

std::string sd_card_usage;

extern "C" const char *get_var_sd_card_usage() {
    return sd_card_usage.c_str();
}

extern "C" void set_var_sd_card_usage(const char *value) {
    sd_card_usage = value;
}

bool sd_card_installed;

extern "C" bool get_var_sd_card_installed() {
    return sd_card_installed;
}

extern "C" void set_var_sd_card_installed(bool value) {
    sd_card_installed = value;
}

std::string nfc_revision;

extern "C" const char *get_var_nfc_revision() {
    return nfc_revision.c_str();
}

extern "C" void set_var_nfc_revision(const char *value) {
    nfc_revision = value;
}

std::string subghz_revision;

extern "C" const char *get_var_subghz_revision() {
    return subghz_revision.c_str();
}

extern "C" void set_var_subghz_revision(const char *value) {
    subghz_revision = value;
}

std::string psram_size;

extern "C" const char *get_var_psram_size() {
    return psram_size.c_str();
}

extern "C" void set_var_psram_size(const char *value) {
    psram_size = value;
}

bool psram_installed;

extern "C" bool get_var_psram_installed() {
    return psram_installed;
}

extern "C" void set_var_psram_installed(bool value) {
    psram_installed = value;
}
