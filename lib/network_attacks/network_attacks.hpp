/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2023 Andrea Canale.
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

#ifndef NETWORKATTACKS_H
#define NETWORKATTACKS_H

#include <stdint.h>

#include "evilportal.hpp"
#include "gui.hpp"

typedef struct {
  const char *ssid;
  const char *password;
} WiFIAPConfig;

typedef struct {
  bool invalid = false;
  bool missing = false;
  uint8_t dest_ip[4];
  uint8_t dest_mac[6];
  uint16_t send_time = 1000;
} ARPoisonerConfig;

class NetworkAttacks {
 private:
  uint8_t generated_clients = 0;
  /// @brief Connect to provided SSID and password from JSON config file
  size_t connect_to_wifi(const char *config);
  EvilPortal *evilPortal;
  bool _evilportal_running = true;
  /// @brief Create the default AP if config is not provided
  void create_default_ap();
  /// @brief Create the AP from config or, if not provided, create the default
  /// AP
  void create_ap();
  ARPoisonerConfig get_arp_config();

 public:
  NetworkAttacks(/* args */);
  ~NetworkAttacks();
  int dhcp_starvation();
  uint8_t get_generated_clients() {
    return generated_clients;
  };  // Try to reduce a bit the overhead
  void init_evilportal();
  void start_evilportal();
  /// @brief Delete evilPortal and disable AP
  void kill_evilportal();
  void stop_evilportal() { _evilportal_running = false; };
  bool evilportal_running() { return _evilportal_running; };
  size_t start_arp_poisoning();
};

#endif
