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

#include "GFXForms.hpp"  // Fix building errors
#include "gui.hpp"
#include "navigation/wifi/wifi_navigation.hpp"
#include "network_attacks.hpp"
#include "network_attacks_tasks.hpp"
#include "ui_tasks/network_attacks/net_attacks_ui_tasks.hpp"
#include "ui_tasks/network_attacks/net_attacks_ui_tasks_types.h"
#include "wifi_attack.hpp"

static NetAttacksTaskArg *task_arg = NULL;
static TaskHandle_t dhcp_glutton_handle = NULL;
static TaskHandle_t dhcp_glutton_ui_handle = NULL;
static TaskHandle_t evilportal_task_handle = NULL;

void start_dhcpglutton(Gui *gui, NetworkAttacks *attack) {
  task_arg = (NetAttacksTaskArg *)malloc(sizeof(NetAttacksTaskArg));
  task_arg->attack = attack;
  task_arg->gui = gui;
  xTaskCreate(&dhcp_starvation_task, "dhcp_glutton", 4000, (void *)task_arg, 5,
              &dhcp_glutton_handle);
  xTaskCreate(&update_dhcp_glutton_clients, "dhcp_glutton_ui_updater", 4000,
              (void *)task_arg, tskIDLE_PRIORITY, &dhcp_glutton_ui_handle);
}

/// @brief Kill DHCP Glutton tasks
void kill_dhcpglutton() {
  vTaskDelete(dhcp_glutton_handle);
  vTaskDelete(dhcp_glutton_ui_handle);
  free(task_arg);
  WiFi.disconnect();
}

void start_evilportal(Gui *gui, NetworkAttacks *attack) {
  attack->init_evilportal();
  set_evilportal_ip(WiFi.softAPIP().toString().c_str());
  task_arg = (NetAttacksTaskArg *)malloc(sizeof(NetAttacksTaskArg));
  task_arg->attack = attack;
  task_arg->gui = gui;
  xTaskCreate(&evilportal_task, "evilportal_processor", 4000, (void *)attack, 5,
              &evilportal_task_handle);
  xTaskCreate(&update_evilportal_requests, "evilportal_requests_updater", 4000,
              (void *)task_arg, tskIDLE_PRIORITY, NULL);
}

void kill_evilportal(NetworkAttacks *attack) {
  attack->stop_evilportal();  // Set evilportal to false so
                              // update_evilportal_requests kill evilportal
  vTaskDelete(evilportal_task_handle);  // This task would ran always
  free(task_arg);
}

TaskHandle_t arp_poisoner_task_handle = NULL;

void start_arp_poisoning(Gui *gui, NetworkAttacks *attack) {
  task_arg = (NetAttacksTaskArg *)malloc(sizeof(NetAttacksTaskArg));
  task_arg->attack = attack;
  task_arg->gui = gui;
  xTaskCreate(&arp_poisoning_task, "arp_poisoner_task", 4000, (void *)task_arg, 5,
              &arp_poisoner_task_handle);
}

void kill_arp_poisoning() {
  WiFi.disconnect(true, true);
  vTaskDelete(arp_poisoner_task_handle);
  free(task_arg);
}