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

#include <Arduino.h>

#include "../../navigation/wifi/wifi_navigation.hpp"
#include "captive_portal_callback.hpp"
#include "net_attacks_ui_tasks_types.h"

#define UPDATE_TIME 1000  // Duration of a cycle

void update_dhcp_glutton_clients(void *pv) {
  NetAttacksTaskArg *params = static_cast<NetAttacksTaskArg *>(pv);
  while (true) {
    set_dhcp_glutton_clients(params->attack->get_generated_clients());
    delay(UPDATE_TIME);
  }
}

void update_evilportal_requests(void *pv) {
  NetAttacksTaskArg *arg = static_cast<NetAttacksTaskArg *>(pv);
  while (arg->attack->evilportal_running()) {
    set_evilportal_requests(get_captured_requests());  // Update requests
    delay(UPDATE_TIME);
  }
  arg->attack->kill_evilportal();  // Kill evilportal when it has finished run
  vTaskDelete(NULL);
}