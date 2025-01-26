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

#include "nfc_attacks.hpp"

void mifare_polling(Gui *gui, NFCAttacks *attacks);
void felica_polling(Gui *gui, NFCAttacks *attacks);
void dump_iso14443a(Gui *gui, NFCAttacks *attacks);
void dump_felica(Gui *gui, NFCAttacks *attacks);
void write_tag(Gui *gui, NFCAttacks *attacks, NFCTag *tag);
void write_felica_tag(Gui *gui, NFCAttacks *attacks, NFCTag *tag);
void write_sectors(Gui *gui, NFCAttacks *attacks, const char *path);
void format_iso14443a(Gui *gui, NFCAttacks *attacks);
void format_felica(Gui *gui, NFCAttacks *attacks);
void bruteforce_tag(Gui *gui, NFCAttacks *attacks);
void reset_uid(void);  // From nfc_tasks.cpp
void reset_felica(void);
void destroy_tasks(NFCAttacks *attacks);
void emulate_iso14443a_tag(uint8_t *uid, NFCAttacks *attacks);
void emulate_iso18092_tag(uint8_t *idm, uint8_t *pmm, uint8_t *sys_code, NFCAttacks *attacks);
void stop_emulate();
void read_emv_card_attack(Gui *gui, NFCAttacks *nfc_attacks);