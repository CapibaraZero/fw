#include "nfc_attacks.hpp"
#include "nfc_tasks_types.h"

bool polling_in_progress = false;
bool dump_in_progress = false;
bool format_in_progress = false;
bool bruteforce_in_progress = false;

static uint8_t uid[8];
static uint8_t uid_length = 0;

static uint8_t idm[8] = { 0 };
static uint8_t pmm[8] = { 0 };
static uint16_t sys_code = 0;

void reset_uid(void) {
    memset(uid, 0, 8);
    uid_length = 0;
}

void reset_felica(void) {
    memset(idm, 0, 8);
    memset(pmm, 0, 8);
    sys_code = 0;
}

void mifare_polling_task(void *pv) {
    polling_in_progress = true;
    NFCTasksParams *params =  static_cast<NFCTasksParams *>(pv);
    Serial0.println("Start polling task");
    while (uid_length == 0)
    {
        params->attacks->read_uid(uid, &uid_length);
        delay(500);
    }
    Serial0.println("Card found");
    params->gui->reset();
    params->gui->set_current_position(2);
    params->gui->init_nfc_polling_result_gui(uid, uid_length);
    free(pv);
    polling_in_progress = false;
    vTaskDelete(NULL);
}

void felica_polling_task(void *pv) {
    polling_in_progress = true;
    NFCTasksParams *params =  static_cast<NFCTasksParams *>(pv);
    Serial0.println("Start polling task");
    while (sys_code == 0)
    {
        params->attacks->detect_felica(idm, pmm, &sys_code);
        delay(500);
    }    
    Serial0.print("Sys code: ");
    Serial0.println(sys_code, HEX);
    // Serial0.println("Card found");
    params->gui->reset();
    params->gui->init_nfc_felica_polling_result_gui(idm, pmm, sys_code);
    params->gui->set_current_position(4);
    free(pv);
    polling_in_progress = false;
    vTaskDelete(NULL);
}

void get_uid(uint8_t *_uid, uint8_t *_uid_length) {
    memcpy(_uid, uid, uid_length);
    *_uid_length = uid_length;
}

void get_card_info(uint8_t *_idm, uint8_t *_pmm, uint16_t *_sys_code) {
    _idm = idm;
    _pmm = pmm;
    *_sys_code = sys_code;
}

void goto_home(NFCTasksParams *params) {
    // Go to home. TODO: Port this in NFCNavigation
    params->gui->reset();
    params->gui->init_gui();
    params->gui->nfc_cleanup();
    params->gui->set_current_position(0);
    params->gui->set_selected_widget(0, true);
    reset_uid();
}

void dump_iso14443a_task(void *pv) {
    dump_in_progress = true;
    NFCTasksParams *params =  static_cast<NFCTasksParams *>(pv);
    DumpResult *result = (DumpResult *)malloc(sizeof(DumpResult));
    NFCTag tag = params->attacks->dump_tag(result);
    params->gui->set_dumped_sectors(tag.get_blocks_count() - result->unreadable - result->unauthenticated);
    params->gui->set_unreadable_sectors(result->unreadable + result->unauthenticated);
    params->attacks->set_scanned_tag(&tag);
    delay(10000);
    goto_home(params);
    free(pv);
    dump_in_progress = false;
    vTaskDelete(NULL);
}

void dump_felica_task(void *pv) {
    dump_in_progress = true;
    NFCTasksParams *params =  static_cast<NFCTasksParams *>(pv);
    // DumpResult *result = (DumpResult *)malloc(sizeof(DumpResult));
    uint8_t unreadable = 0;
    NFCTag tag = params->attacks->felica_dump(14, &unreadable);
    Serial0.println("Finished2");
    Serial0.printf("Felica dump: %d\n", unreadable);
    params->gui->set_dumped_sectors(14 - unreadable);
    params->gui->set_unreadable_sectors(unreadable);
    params->attacks->set_scanned_tag(&tag);
    delay(10000);
    goto_home(params);
    free(pv);
    dump_in_progress = false;
    vTaskDelete(NULL);
}

void format_iso14443a_task(void *pv) {
    format_in_progress = true;
    NFCTasksParams *params =  static_cast<NFCTasksParams *>(pv);
    uint8_t unformattable = 0;
    if(uid_length == 7)
        unformattable = params->attacks->format_ntag(NTAG213_PAGES);
    else
        unformattable = params->attacks->format_tag();
    Serial0.printf("Unformattable sectors: %d\n", unformattable);
    params->gui->set_unformatted_sectors(uid_length == 4 ? MIFARE_CLASSIC_BLOCKS : NTAG213_PAGES, unformattable);
    delay(10000);
    goto_home(params);
    free(pv);
    format_in_progress = false;
    vTaskDelete(NULL);
}

void format_felica_task(void *pv) {
    format_in_progress = true;
    NFCTasksParams *params =  static_cast<NFCTasksParams *>(pv);
    params->gui->set_unformatted_sectors(14, params->attacks->felica_format(14));
    delay(10000);
    goto_home(params);
    free(pv);
    format_in_progress = false;
    vTaskDelete(NULL);
}

void bruteforce_iso14443a_task(void *pv) {
    bruteforce_in_progress = true;
    NFCTasksParams *params =  static_cast<NFCTasksParams *>(pv);
    params->gui->nfc_bruteforce_found_key(params->attacks->bruteforce());
    delay(10000);
    goto_home(params);
    free(pv);
    bruteforce_in_progress = false;
    vTaskDelete(NULL);
}

void bruteforce_update_ui_task(void *pv) {
    NFCTasksParams *params =  static_cast<NFCTasksParams *>(pv);
    while(params->attacks->get_bruteforce_status()) {
        params->gui->nfc_bruteforce_set_tried_key(params->attacks->get_tried_keys());
        delay(1000);
    }
    params->gui->nfc_bruteforce_set_tried_key(params->attacks->get_tried_keys());
    // We don't need free(pv) here because we share same pointer between bruteforce tasks
    vTaskDelete(NULL);
}