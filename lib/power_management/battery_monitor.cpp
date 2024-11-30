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

#include "../../include/battery_level.h"
#include "../../include/pins.h"
#ifdef LILYGO_T_EMBED_CC1101
#include "bq27220.h"
BQ27220 bq;
#endif

int read_battery_level() {
  int battery_level = 0;
#if defined(BATTERY_MONITOR) || defined(BQ27220_BATTERY)
#ifdef BATTERY_MONITOR
  battery_level = analogRead(BATTERY_MONITOR);
  battery_level = map(battery_level, MIN_ANALOG_VALUE, MAX_ANALOG_VALUE,
                      MIN_LEVEL, MAX_LEVEL);
#elif defined(BQ27220_BATTERY)
  int remain_mah = bq.getRemainCap();
  int full_mah = bq.getFullChargeCap();
  battery_level = map(remain_mah, 0, full_mah, 0, 100);
#endif
#endif
  return battery_level;
}