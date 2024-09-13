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

#include "../../../../include/battery_level.h"
#include "battery_monitor.hpp"
#include "battery_monitor_task_types.h"

void battery_monitor_task(void *pv) {
  BatteryMonitorTaskParams *params =
      static_cast<BatteryMonitorTaskParams *>(pv);

  while (true) {
    if (params->visible) {
      params->lock = true;
      params->page->set_battery_level();
      params->lock = false;
    }
    delay(TASK_POLLING_RATE);
  }
}