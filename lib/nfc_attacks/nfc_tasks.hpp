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

#ifndef NFC_TASKS_H
#define NFC_TASKS_H

#include "nfc_attacks.hpp"

extern bool polling_in_progress;
extern bool dump_in_progress;
extern bool format_in_progress;
extern bool bruteforce_in_progress;

void mifare_polling_task(void *pv);
void felica_polling_task(void *pv);
void get_uid(uint8_t *_uid, uint8_t *_length);
void get_card_info(uint8_t *_idm, uint8_t *_pmm, uint16_t *_sys_code);
void dump_iso14443a_task(void *pv);
void dump_felica_task(void *pv);
void write_nfc_sectors(void *pv);
void format_iso14443a_task(void *pv);
void format_update_ui_task(void *pv);
void format_felica_task(void *pv);
void bruteforce_iso14443a_task(void *pv);
void bruteforce_update_ui_task(void *pv);
void emulate_iso14443anfc(void *pv);
void emulate_iso18092nfc(void *pv);
void read_emv_card_task(void *pv);
#endif