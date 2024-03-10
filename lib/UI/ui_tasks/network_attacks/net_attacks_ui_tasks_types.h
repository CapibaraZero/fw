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

#ifndef NETWORK_ATTACKS_UI_TASKS_TYPES_H
#define NETWORK_ATTACKS_UI_TASKS_TYPES_H

#include "GFXForms.hpp"  // Fix building errors
#include "gui.hpp"
#include "network_attacks.hpp"
#include "wifi_attack.hpp"

typedef struct {
  Gui *gui;
  NetworkAttacks *attack;
} NetAttacksTaskArg;

#endif