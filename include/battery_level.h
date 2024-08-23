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

#define MIN_ANALOG_VALUE 0  // Low analog value, read using analogRead()
#define MAX_ANALOG_VALUE 3300   // High analog value, read using analogRead()
#define MIN_LEVEL 0 // Minimium battery level in percentage
#define MAX_LEVEL 100   // Maximium battery level in percentage
#define TASK_POLLING_RATE 10000 // Level updater timeout in milliseconds(it will update every x ms)