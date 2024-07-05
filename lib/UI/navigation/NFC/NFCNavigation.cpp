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

#include "../../../../include/debug.h"
#include "../../../../include/pins.h"
#include "../navigation.hpp"
#include "fm.hpp"
#include "gui.hpp"
#include "nfc_attacks_btn.hpp"
#include "pages/NFC/FeliCaPages/NFCFelicaPollingResultPage.hpp"
#include "pages/NFC/NFCBruteforceTagPage.hpp"
#include "pages/NFC/NFCDumpResultPage.hpp"
#include "pages/NFC/NFCFormatResultPage.hpp"
#include "pages/NFC/NFCMainPage.hpp"
#include "pages/NFC/NFCPollingResultPage.hpp"
#include "pages/NFC/NFCPollingWaitingPage.hpp"
#include "pages/NFC/NFCWriteResultPage.hpp"

static Gui *gui;
static NFCAttacks *nfc_attacks = nullptr;
static NFCMainPage *nfc_main_page = nullptr;
static NFCPollingWaitingPage *nfc_polling_waiting_page = nullptr;
static NFCPollingResultPage *nfc_polling_result_page = nullptr;
static NFCDumpResultPage *nfc_dump_result_page = nullptr;
static NFCFormatResultPage *nfc_format_result_page = nullptr;
static NFCBruteforceTagPage *nfc_bruteforce_tag_page = nullptr;
static NFCFelicaPollingResultPage *nfc_felica_polling_result_page = nullptr;

#define DUMP_SAVE_PATH                                            \
    ((String) "/NFC/dumps/" + (String)millis() + (String) ".hex") \
        .c_str()  // TODO: Use UID + millis as identifier

void goto_nfc_gui() {
    gui->reset();
    nfc_main_page = new NFCMainPage(2, 0, 1, gui->get_screen(), gui);
    gui->set_current_page(nfc_main_page);
    nfc_main_page->display();
}

void goto_nfc_polling_waiting_gui() {
    gui->reset();
    nfc_polling_waiting_page =
        new NFCPollingWaitingPage(0, 0, 0, gui->get_screen(), gui);
    gui->set_current_page(nfc_polling_waiting_page);
    nfc_polling_waiting_page->display();
}

void goto_nfc_dump_result_gui() {
    gui->reset();
    nfc_dump_result_page =
        new NFCDumpResultPage(4, 4, 0, gui->get_screen(), gui);
    gui->set_current_page(nfc_dump_result_page);
    nfc_dump_result_page->display();
}

void goto_nfc_polling_result_gui(uint8_t *uid, uint8_t len, const char *tag_name) {
    gui->reset();
    nfc_polling_result_page =
        new NFCPollingResultPage(3, 2, 1, gui->get_screen(), gui);
    gui->set_current_page(nfc_polling_result_page);
    nfc_polling_result_page->display(uid, len, tag_name);
}

// Clean all pointers to avoid problems with memory
// The pages is removed by GUI class
void nfc_cleanup() {
    nfc_polling_result_page = nullptr;
    nfc_dump_result_page = nullptr;
    // nfc_write_result_page = nullptr;
    nfc_format_result_page = nullptr;
    nfc_bruteforce_tag_page = nullptr;
}

void goto_home() {
    reset_uid();
    reset_felica();
    nfc_cleanup();
    init_main_gui();
}

void save_dump_to_sd() {
    Serial.println("save_dump_to_sd");
    save_file(DUMP_SAVE_PATH, nfc_attacks->get_scanned_tag()->get_data(), 224);
    Serial.println("save_dump_to_sd2");
    goto_home();
}

void write_hex_to_tag() {
    gui->reset();
    // gui->init_nfc_write_result_gui();
    NFCTag tag_to_write = nfc_attacks->get_tag_towrite(7);
    // TODO: If empty block the process
    write_tag(gui, nfc_attacks, &tag_to_write);
}

void format_tag() {
    gui->reset();
    nfc_format_result_page =
        new NFCFormatResultPage(0, 0, 0, gui->get_screen(), gui);
    gui->set_current_page(nfc_format_result_page);
    nfc_format_result_page->display();
}

void bruteforce_a_tag() {
    gui->reset();
    nfc_bruteforce_tag_page =
        new NFCBruteforceTagPage(0, 0, 0, gui->get_screen(), gui);
    gui->set_current_page(nfc_bruteforce_tag_page);
    nfc_bruteforce_tag_page->display();
    bruteforce_tag(gui, nfc_attacks);
}

void stop_nfc_polling() {
    reset_uid();
    reset_felica();
    gui->reset();
    nfc_cleanup();
    destroy_tasks();
    // gui->init_nfc_gui();
}

void nfc_mifare_polling() {
    goto_nfc_polling_waiting_gui();
    mifare_polling(gui, nfc_attacks);
}

void nfc_felica_polling() {
    goto_nfc_polling_waiting_gui();
    felica_polling(gui, nfc_attacks);
}

void write_felica_tag() {
    gui->reset();
    // gui->init_nfc_write_result_gui();
    // TODO: If empty block the process
    NFCTag tag_to_write = nfc_attacks->get_felica_towrite();
    write_felica_tag(gui, nfc_attacks, &tag_to_write);
    // write_tag(gui, nfc_attacks, &tag_to_write);
}

void init_nfc_felica_polling_result_gui(uint8_t *idm, uint8_t *pmm,
                                        uint16_t sys_code) {
    nfc_felica_polling_result_page =
        new NFCFelicaPollingResultPage(5, 4, 1, gui->get_screen(), gui);
    nfc_felica_polling_result_page->display(idm, pmm, sys_code);
    nfc_polling_waiting_page = nullptr;
}

void felica_dump() {
    goto_nfc_dump_result_gui();
    dump_felica(gui, nfc_attacks);
}

void set_dumped_sectors(int sectors) {
    nfc_dump_result_page->set_dumped(sectors);
};
void set_unreadable_sectors(int sectors) {
    nfc_dump_result_page->set_unreadable(sectors);
};
void set_unauthenticated_sectors(int sectors) {
    nfc_dump_result_page->set_unauthenticated(sectors);
};
void set_unwritable_sectors(uint8_t tot, uint8_t sectors) {
    // nfc_write_result_page->set_wrote_sectors(tot - sectors);
    // nfc_write_result_page->set_unwritable_sectors(sectors);
};
void set_unformatted_sectors(uint8_t tot, uint8_t unformatted) {
    nfc_format_result_page->set_formatted(tot - unformatted);
    nfc_format_result_page->set_unauthenticated(unformatted);
}
void nfc_bruteforce_found_key() { nfc_bruteforce_tag_page->set_found_key(); };
void nfc_bruteforce_set_tried_key(uint8_t attemps) {
    nfc_bruteforce_tag_page->update_tried_keys(attemps);
};
bool nfc_bruteforce_page_visible() {
    return nfc_bruteforce_tag_page != nullptr;
};

void init_nfc_navigation(Gui *_gui) {
    LOG_INFO("Init NFC Navigation");
    gui = _gui;
    Wire.begin(PN532_SDA, PN532_SCL);
    nfc_attacks = new NFCAttacks();
}