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

#include "../../include/debug.h"
#include "nfc_attacks.hpp"
#include "nfc_tasks.hpp"
#include "nfc_tasks_types.h"

static NFCTasksParams *params = NULL;
static TaskHandle_t polling_task_handle = NULL;
static TaskHandle_t dump_task_handle = NULL;
static TaskHandle_t format_task_handle = NULL;
static TaskHandle_t bruteforce_task_handle = NULL;
static TaskHandle_t ui_updater_task_handle = NULL;
static TaskHandle_t nfc_emulate_handle = NULL;
static TaskHandle_t emv_reader_handle = NULL;

void mifare_polling(Gui *gui, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->gui = gui;
  xTaskCreate(mifare_polling_task, "mifare_polling", 4096, (void *)params, 5,
              &polling_task_handle);
}

void felica_polling(Gui *gui, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->gui = gui;
  xTaskCreate(felica_polling_task, "felica_polling", 4096, (void *)params, 5,
              &polling_task_handle);
}
void dump_iso14443a(Gui *gui, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->gui = gui;
  xTaskCreate(dump_iso14443a_task, "dump_iso14443a", 4096, (void *)params, 5,
              &dump_task_handle);
}

void dump_felica(Gui *gui, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->gui = gui;
  xTaskCreate(dump_felica_task, "dump_felica", 4096, (void *)params, 5,
              &dump_task_handle);
}

void write_felica_tag(Gui *gui, NFCAttacks *attacks, NFCTag *tag) {
  attacks->felica_write(tag);
}

void write_sectors(Gui *gui, NFCAttacks *attacks, const char *path) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->gui = gui;
  params->path = (char *)path;
  xTaskCreate(write_nfc_sectors, "write_nfc_sectios", 8192, (void *)params, 5,
              NULL);
}

void format_iso14443a(Gui *gui, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->gui = gui;
  xTaskCreate(format_iso14443a_task, "format_nfc_tag", 20000, (void *)params, 5,
              &format_task_handle);
  xTaskCreate(format_update_ui_task, "format_ui_updated", 4096, (void *)params,
              5, &ui_updater_task_handle);
}

void format_felica(Gui *gui, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->gui = gui;
  xTaskCreate(format_felica_task, "felica_format", 4096, (void *)params, 5,
              &format_task_handle);
}

void bruteforce_tag(Gui *gui, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->gui = gui;
  xTaskCreate(bruteforce_iso14443a_task, "bruteforce_iso14443a", 20000,
              (void *)params, 5, &bruteforce_task_handle);
  xTaskCreate(bruteforce_update_ui_task, "bruteforce_update_ui", 4096,
              (void *)params, 5, &ui_updater_task_handle);
}

void emulate_iso14443a_tag(uint8_t *uid, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->uid = uid;
  xTaskCreate(emulate_iso14443anfc, "emulate_nfc", 4000, (void *) params, 5, &nfc_emulate_handle);
}

void emulate_iso18092_tag(uint8_t *idm, uint8_t *pmm, uint8_t *sys_code, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->idm = idm;
  params->pmm = pmm;
  // params->sys_code = sys_code;
  memcpy(params->sys_code, sys_code, 2);
  xTaskCreate(emulate_iso18092nfc, "emulate_nfc", 4000, (void *) params, 5, &nfc_emulate_handle);
}

void stop_emulate() {
  vTaskDelete(nfc_emulate_handle);
  nfc_emulate_handle = NULL;
}

bool reading_emv = false;

void read_emv_card_attack(Gui *gui, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->gui = gui;
  xTaskCreate(read_emv_card_task, "read_emv_card", 4000, (void *) params, 5, &emv_reader_handle);
  reading_emv = true;
}

void destroy_tasks(NFCAttacks *attacks) {
  attacks->power_down();
  if (polling_in_progress) {
    vTaskDelete(polling_task_handle);
    polling_task_handle = NULL;
  } else if (dump_in_progress) {
    vTaskDelete(dump_task_handle);
    dump_task_handle = NULL;
  } else if (format_in_progress) {
    vTaskDelete(format_task_handle);
    format_task_handle = NULL;
    vTaskDelete(ui_updater_task_handle);
    ui_updater_task_handle = NULL;
  } else if (bruteforce_in_progress) {
    vTaskDelete(bruteforce_task_handle);
    bruteforce_task_handle = NULL;
    vTaskDelete(ui_updater_task_handle);
    ui_updater_task_handle = NULL;
  }
  if(nfc_emulate_handle != NULL) {
    vTaskDelete(nfc_emulate_handle);
    nfc_emulate_handle = NULL;
  }
  if(emv_reader_handle != NULL && reading_emv) {
    vTaskDelete(emv_reader_handle);
    emv_reader_handle = NULL;
  }
}