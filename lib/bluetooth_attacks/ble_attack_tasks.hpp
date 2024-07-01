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

#ifndef BLE_ATTACK_TASKS_H
#define BLE_ATTACK_TASKS_H

void ble_scan_task(void *pv);
void ble_sniff_task(void *pv);
void applejuice_task(void *pv);
void samsung_ble_spam_task(void *pv);
void swift_pair_spam_task(void *pv);
void fast_pair_spam_task(void *pv);
#endif
