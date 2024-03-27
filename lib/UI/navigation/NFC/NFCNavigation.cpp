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

#include "../navigation.hpp"
#include "fm.hpp"
#include "gui.hpp"
#include "nfc_attacks_btn.hpp"
#include "debug.h"

static Gui *gui;
static NFCAttacks *nfc_attacks = nullptr;

#define DUMP_SAVE_PATH                                          \
  ((String) "/NFC/dumps/" + (String)millis() + (String) ".hex") \
      .c_str()  // TODO: Use UID + millis as identifier

void goto_nfc_gui() {
  gui->reset();
  gui->set_current_position(0);
  gui->init_nfc_gui();
}

void goto_nfc_polling_waiting_gui() {
  gui->reset();
  gui->set_current_position(0);
  gui->init_nfc_polling_waiting_gui();
}

void goto_nfc_dump_result_gui() {
  gui->reset();
  gui->init_nfc_dump_result_gui();
  gui->set_current_position(2);
}

void goto_home() {
  reset_uid();
  reset_felica();
  gui->reset();
  gui->nfc_cleanup();
  // destroy_tasks();
  // delete nfc_attacks;
  // nfc_attacks = nullptr;
  init_main_gui();
}

void save_dump_to_sd() {
  save_file(DUMP_SAVE_PATH, nfc_attacks->get_scanned_tag()->get_data(), 224);
  goto_home();
}

void write_hex_to_tag() {
  gui->reset();
  gui->init_nfc_write_result_gui();
  gui->set_current_position(3);
  NFCTag tag_to_write = nfc_attacks->get_tag_towrite(7);
  // TODO: If empty block the process
  write_tag(gui, nfc_attacks, &tag_to_write);
}

void format_tag() {
  gui->reset();
  gui->init_nfc_format_result_gui();
  // gui->set_current_position(3);
}

void bruteforce_tag() {
  gui->reset();
  gui->init_nfc_bruteforce_gui();
  gui->set_current_position(3);
  bruteforce_tag(gui, nfc_attacks);
}

void return_to_nfc_polling_gui() {
  gui->reset();
  // gui->destroy_nfc_dump_result_gui();
  // destroy_tasks();
  gui->set_current_position(2);
  // gui->set_selected_widget(2, true);
  gui->return_to_nfc_polling_gui();
}

void stop_nfc_polling() {
  reset_uid();
  reset_felica();
  gui->reset();
  gui->nfc_cleanup();
  destroy_tasks();
  gui->init_nfc_gui();
}

void nfc_submenu_handler(int pos) {
  switch (pos) {
    case 0:  // Start polling
      gui->ok(goto_nfc_polling_waiting_gui);
      mifare_polling(gui, nfc_attacks);
      break;
    case 1:
      gui->ok(goto_nfc_polling_waiting_gui);
      felica_polling(gui, nfc_attacks);
      break;
    case 2:
      gui->ok(goto_home);
      break;
    default:
      break;
  }
}

#define RESULT_DUMP_POS 2
// #define RESULT_FORMAT_POS 3
#define RESULT_BRUTEFORCE_POS 3
#define RESULT_GO_BACK_POS 4

void nfc_polling_submenu_handler(int pos) {
  switch (pos) {
    case RESULT_DUMP_POS:  // Start polling
      gui->ok(goto_nfc_dump_result_gui);
      dump_iso14443a(gui, nfc_attacks);
      break;
    // case RESULT_FORMAT_POS:
    //   // gui->ok(write_hex_to_tag);
    //   gui->ok(format_tag);
    //   format_iso14443a(gui, nfc_attacks);
    //   break;
    case RESULT_BRUTEFORCE_POS:
      gui->ok(bruteforce_tag);
      break;
    case RESULT_GO_BACK_POS:
      gui->ok(goto_nfc_gui);
      gui->destroy_nfc_polling_gui();
      reset_uid();
      break;
    default:
      break;
  }
}

#define SAVE_DUMP_TO_SD_POS 2
// #define DUMP_GO_BACK_POS 5
// #define DUMP_GO_HOME_POS 4

void nfc_dump_submenu_handler(int pos) {
  switch (pos) {
    case SAVE_DUMP_TO_SD_POS:  // Start polling
      LOG_INFO("Start polling");
      gui->ok(save_dump_to_sd);
      break;
      //   case DUMP_GO_BACK_POS:
      //     LOG_INFO("Return to NFC");
      //     gui->destroy_nfc_dump_result_gui();
      //     gui->ok(return_to_nfc_polling_gui);
      //     break;
      // case DUMP_GO_HOME_POS:
      //   LOG_INFO("GOTO HOME");
      //   gui->ok(goto_home);
      //   gui->destroy_nfc_polling_gui();
      //   break;
    default:
      break;
  }
}

// #define FORMAT_GO_BACK 3
// #define FORMAT_GO_HOME 4

void nfc_format_submenu_handler(int pos) {
  // switch(pos) {
  //   case FORMAT_GO_BACK:
  //     gui->ok(return_to_nfc_polling_gui);
  //     gui->destroy_nfc_format_result_gui();
  //     break;
  //   case FORMAT_GO_HOME:
  // gui->ok(goto_home);
  //     break;
  // }
}

void nfc_bruteforce_submenu_handler(int pos) {
  // nfc_format_submenu_handler(pos);
  // gui->destroy_nfc_bruteforce_gui();
  // reset_uid();
  // gui->reset();
  // gui->nfc_cleanup();
  // // destroy_tasks();
  // init_main_gui();
}

#define FELICA_DUMP_TO_SD 4
#define FELICA_GO_BACK 5
// #define FELICA_WRITE_TAG 5
// #define FELICA_FORMAT_TAG 6

void write_felica_tag() {
  gui->reset();
  gui->init_nfc_write_result_gui();
  gui->set_current_position(3);
  // TODO: If empty block the process
  NFCTag tag_to_write = nfc_attacks->get_felica_towrite();
  write_felica_tag(gui, nfc_attacks, &tag_to_write);
  // write_tag(gui, nfc_attacks, &tag_to_write);
}

void nfc_felica_polling_submenu_handler(int pos) {
  Serial.printf("NFC FELICA POSITION: %d\n", pos);
  switch (pos) {
    case FELICA_DUMP_TO_SD:
      LOG_INFO("DUmp FeliCa SD");
      gui->ok(goto_nfc_dump_result_gui);
      dump_felica(gui, nfc_attacks);
      break;
    case FELICA_GO_BACK:
      gui->ok(goto_nfc_gui);
      gui->destroy_nfc_polling_gui();
      reset_felica();
      break;
    // case FELICA_WRITE_TAG:
    //   LOG_INFO("Write FeliCa Tag");
    //   gui->ok(write_felica_tag);
    //   // write_felica(gui, nfc_attacks);
    //   break;
    // case FELICA_FORMAT_TAG:
    //   LOG_INFO("Format FeliCa Tag");
    //   gui->ok(format_tag);
    //   format_felica(gui, nfc_attacks);
    //   break;
    default:
      break;
  }
}

void init_nfc_navigation(Gui *_gui) {
  LOG_INFO("Init NFC Navigation");
  gui = _gui;
  nfc_attacks = new NFCAttacks();
}