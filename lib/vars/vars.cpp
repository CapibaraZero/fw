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