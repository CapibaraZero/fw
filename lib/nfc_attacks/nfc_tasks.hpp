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
void format_felica_task(void *pv);
void bruteforce_iso14443a_task(void *pv);
void bruteforce_update_ui_task(void *pv);
#endif