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

#include "ui_tasks/network_attacks/net_attacks_ui_tasks_types.h"

void dhcp_starvation_task(void *pv) {
  NetAttacksTaskArg *params = static_cast<NetAttacksTaskArg *>(pv);
  size_t ret = params->attack->dhcp_starvation();
  if(ret == 0) {
    params->gui->show_error_page("Missing config");
  } else if(ret == 1){
    params->gui->show_error_page("Invalid config");
  };
  vTaskDelete(NULL);
}

void evilportal_task(void *pv) {
  NetworkAttacks *params = static_cast<NetworkAttacks *>(pv);
  params->start_evilportal();
}

void arp_poisoning_task(void *pv) {
  NetAttacksTaskArg *params = static_cast<NetAttacksTaskArg *>(pv);
  size_t ret = params->attack->start_arp_poisoning();
  if(ret == 0) {
    params->gui->show_error_page("Missing config");
  } else if(ret == 1){
    params->gui->show_error_page("Invalid config");
  };
  vTaskDelete(NULL);
}