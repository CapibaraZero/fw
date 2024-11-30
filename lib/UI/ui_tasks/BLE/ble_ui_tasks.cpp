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

#include "../../navigation/BLE/ble_navigation.hpp"
#include "ble_ui_tasks_types.h"
#include "bluetooth_attacks.hpp"

void update_ble_sniffed_packets(void *pv) {
  BLEUITaskParameters *params = static_cast<BLEUITaskParameters *>(pv);
  while (params->ble_attack->is_sniffing()) {
    update_ble_packets_count(params->ble_attack->get_sniffed_packets());
    delay(1000);
  }
  vTaskDelete(NULL);
}

void update_ble_scan_progress(void *pv) {
  BLEUITaskParameters *params = static_cast<BLEUITaskParameters *>(pv);
  const int scan_time = params->ble_attack->get_scanning_time() / 1000;
  const double progress_step = 100.0 / scan_time;
  const double lower_limit = 100 + progress_step - 1;  // While limit
  double progress = progress_step;
  while (progress < lower_limit)  // Until 100%
  {
    //  set_ble_progress(
    //       (char *)(String(progress) + String("%")).c_str());
    //  set_ble_adv_devices_text(
    //       params->ble_attack->get_scanned_devices());
    progress += progress_step;
    delay(progress_step);  // scan time
  }
  vTaskDelete(NULL);
}
