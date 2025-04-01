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

#ifndef NFC_ACTIONS_H
#define NFC_ACTIONS_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

void action_go_to_nfc_polling(lv_event_t *e);
void action_stop_nfc_polling(lv_event_t *e);
void action_go_to_nfc_page(lv_event_t *e);
void action_go_to_nfc_format(lv_event_t *e);
void action_nfc_start_emulation(lv_event_t *e);
void action_nfc_stop_emulation(lv_event_t *e);
void action_go_to_nfc_bruteforce(lv_event_t *e);
void write_sectors_wrapper(lv_event_t *e);
void action_go_to_nfc_felica_dump(lv_event_t *e);
void action_go_to_nfc_read_emv(lv_event_t *e);

#ifdef __cplusplus
}
#endif

#endif
