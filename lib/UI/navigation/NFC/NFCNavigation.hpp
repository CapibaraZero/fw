/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or https://capibarazero.github.io/).
 * Copyright (c) 2024 Andrea Canale.
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
void nfc_submenu_handler(int pos);
void nfc_polling_submenu_handler(int pos);
void nfc_dump_submenu_handler(int pos);
void nfc_format_submenu_handler(int pos);
void goto_nfc_gui();
void stop_nfc_polling();
void nfc_bruteforce_submenu_handler(int pos);
void nfc_felica_polling_submenu_handler(int pos);
#endif