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

#include "screens.h"
#include "ui.h"
#include "NFCTag.hpp"
#include "nfc_attacks_btn.hpp"
#include "vars.h"

NFCAttacks *_nfc_attacks = nullptr;
static bool nfc_initialized = false;

extern uint16_t sys_code; // From nfc_tasks

void init_nfc_navigation() {
  sys_code = 0; // Cleanup from previous polling
  if (!nfc_initialized) {
    LOG_INFO("Init NFC Navigation");
#ifndef LILYGO_T_EMBED_CC1101
    // Already initialized in setup
    Wire.begin(PN532_SDA, PN532_SCL);
#endif
    _nfc_attacks = new NFCAttacks();
    if(!_nfc_attacks->begin()) {
      //gui->show_error_page("Missing PN532");
    }
    nfc_initialized = true;
  }
}

extern "C" void action_go_to_nfc_page(lv_event_t *e) {
    init_nfc_navigation();
    create_screen_nfc_page();
    loadScreen(SCREEN_ID_NFC_PAGE);
}

extern "C" void action_go_to_nfc_polling(lv_event_t *e) {
    int mode = (int)e->user_data;

    create_screen_nfc_polling();
    loadScreen(SCREEN_ID_NFC_POLLING);

    if(mode == 0)
      mifare_polling(_nfc_attacks);
    else
      felica_polling(_nfc_attacks);
}

extern "C" void action_stop_nfc_polling(lv_event_t *e) {
    destroy_tasks(_nfc_attacks);
    create_screen_nfc_page();
    loadScreen(SCREEN_ID_NFC_PAGE);
}

extern "C" void action_go_to_nfc_format(lv_event_t *e) {
  // Cleanup from previous write
  set_var_nfc_written_sectors("");
  set_var_nfc_unwritable_sectors("");  

  create_screen_nfc_write_page();
  loadScreen(SCREEN_ID_NFC_WRITE_PAGE);

  format_iso14443a(_nfc_attacks);
}

extern "C" void action_nfc_start_emulation(lv_event_t *e) {
  create_screen_nfc_emulate_page();
  loadScreen(SCREEN_ID_NFC_EMULATE_PAGE);

  int mode = (int)e->user_data;

  if(mode == 0) {
    extern uint8_t uid[8];
    emulate_iso14443a_tag(uid, _nfc_attacks);
  } else {
    extern uint8_t idm[8];
    extern uint8_t pmm[8];

    // Prepare syscode for emulation
    uint8_t _sys_code[2];
    _sys_code[0] = sys_code >> 8;
    _sys_code[1] = sys_code & 0xff;

    emulate_iso18092_tag(idm, pmm, _sys_code, _nfc_attacks);
  }
}

extern "C" void action_nfc_stop_emulation(lv_event_t *e) {
  stop_emulate(); // Stop emulation
  action_go_to_nfc_page(e); // Return to NFC Page
}

extern "C" void action_go_to_nfc_bruteforce(lv_event_t *e) {
    create_screen_nfc_bruteforce_page();
    loadScreen(SCREEN_ID_NFC_BRUTEFORCE_PAGE);

    bruteforce_tag(_nfc_attacks);
}

extern "C" void write_sectors_wrapper(lv_event_t *e) {
  const char *path = (const char *)e->user_data;

  set_var_nfc_written_sectors("");
  set_var_nfc_unwritable_sectors("");  

  create_screen_nfc_write_page();
  loadScreen(SCREEN_ID_NFC_WRITE_PAGE);

  write_sectors(_nfc_attacks, path);
}

extern "C" void action_go_to_nfc_felica_dump(lv_event_t *e) {
  create_screen_nfc_felica_read();
  loadScreen(SCREEN_ID_NFC_FELICA_READ);

  dump_felica(_nfc_attacks);
}

extern "C" void action_go_to_nfc_read_emv(lv_event_t *e) {
  set_var_nfc_emv_type("Reading EMV...");
  set_var_nfc_emv_card_number("");
  set_var_nfc_emv_card_expire("");
  set_var_nfc_emv_card_issue("");

  create_screen_nfcemv_read();
  loadScreen(SCREEN_ID_NFCEMV_READ);

  read_emv_card_attack(_nfc_attacks);
}