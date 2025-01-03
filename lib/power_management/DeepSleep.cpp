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

#include "../../include/pins.h"
#include "Arduino.h"

#if defined(STANDBY_BTN) && defined(WAKEUP_PIN)

#define GPIO_BITMASK(GPIO) (1ULL << GPIO)

static void IRAM_ATTR standby() {
  digitalWrite(15, LOW);  // Power off CC1101 and LED
  esp_sleep_enable_ext1_wakeup(GPIO_BITMASK(WAKEUP_PIN),
                               ESP_EXT1_WAKEUP_ANY_LOW);
  esp_deep_sleep_start();
}

#endif

#if defined(WAKEUP_PIN)

void go_deep_sleep() {  // For usage in settings
  digitalWrite(15, LOW);  // Power off CC1101 and LED
  esp_sleep_enable_ext1_wakeup(GPIO_BITMASK(WAKEUP_PIN),
                               ESP_EXT1_WAKEUP_ANY_LOW);
  esp_deep_sleep_start();
}

#endif

#if defined(STANDBY_BTN) && defined(WAKEUP_PIN)
void enable_deep_sleep() {
  pinMode(STANDBY_BTN, INPUT);
  attachInterrupt(STANDBY_BTN, standby, FALLING);
}
#endif