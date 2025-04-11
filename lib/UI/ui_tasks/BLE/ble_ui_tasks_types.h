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

#ifndef BLE_UI_TASKS_TYPES_H
#define BLE_UI_TASKS_TYPES_H

// Fix building errors
#include "AppleJuice.hpp"
#include "BLEScanner.hpp"
#include "BLESniffer.hpp"
#include "FS.h"
#include "fast_pair_spam.hpp"
#include "microsoft_ble_spam.hpp"
#include "samsung_ble_spam.hpp"
#include "bluetooth_attacks.hpp"

typedef struct {
  BluetoothAttack *ble_attack;
} BLEUITaskParameters;

#endif
