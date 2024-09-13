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

#ifndef NFC_NAVIGATION_H
#define NFC_NAVIGATION_H

void init_nfc_navigation(Gui *_gui);
void goto_nfc_gui();
void stop_nfc_polling();
void save_dump_to_sd();
void nfc_mifare_polling();
void nfc_felica_polling();
void goto_home();
void bruteforce_a_tag();
void init_nfc_felica_polling_result_gui(uint8_t *idm, uint8_t *pmm,
                                        uint16_t sys_code);
void set_dumped_sectors(int sectors);
void set_unreadable_sectors(int sectors);
void set_unauthenticated_sectors(int sectors);
void set_unwritable_sectors(uint8_t tot, uint8_t sectors);
void set_unformatted_sectors(uint8_t tot, uint8_t unformatted);
void nfc_bruteforce_found_key();
void nfc_bruteforce_set_tried_key(uint8_t attemps);
void goto_nfc_dump_result_gui();
void goto_nfc_polling_result_gui(uint8_t *uid, uint8_t len,
                                 const char *tag_name);
void felica_dump();
void nfc_cleanup();
#endif