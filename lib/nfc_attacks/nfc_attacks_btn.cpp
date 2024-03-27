#include "nfc_attacks.hpp"
#include "nfc_tasks.hpp"
#include "nfc_tasks_types.h"
#include "../../include/debug.h"

static NFCTasksParams *params = NULL;
static TaskHandle_t polling_task_handle = NULL;
static TaskHandle_t dump_task_handle = NULL;
static TaskHandle_t format_task_handle = NULL;
static TaskHandle_t bruteforce_task_handle = NULL;
static TaskHandle_t bruteforce_ui_task_handle = NULL;

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

void write_tag(Gui *gui, NFCAttacks *attacks, NFCTag *tag) {
  if (tag->is_ntag()) {
    LOG_INFO("Tag is NTAG");
    uint8_t unwritable = attacks->write_ntag(tag);
    Serial.printf("Unwritable sectors: %d\n", unwritable);
    gui->set_unwritable_sectors(tag->get_blocks_count(), unwritable);
  } else {
    LOG_INFO("Tag is not NTAG");
    uint8_t unwritable = attacks->write_tag(tag);
    Serial.printf("Unwritable sectors: %d\n", unwritable);
    gui->set_unwritable_sectors(tag->get_blocks_count(), unwritable);
  }
}

void write_felica_tag(Gui *gui, NFCAttacks *attacks, NFCTag *tag) {
  attacks->felica_write(tag);
}

void format_iso14443a(Gui *gui, NFCAttacks *attacks) {
  /* We delete this after usage, so we need to recreate struct every time */
  params = (NFCTasksParams *)malloc(sizeof(NFCTasksParams));
  params->attacks = attacks;
  params->gui = gui;
  xTaskCreate(format_iso14443a_task, "mifare_polling", 4096, (void *)params, 5,
              &format_task_handle);
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
  xTaskCreate(bruteforce_iso14443a_task, "bruteforce_iso14443a", 4096,
              (void *)params, 5, &bruteforce_task_handle);
  xTaskCreate(bruteforce_update_ui_task, "bruteforce_update_ui", 4096,
              (void *)params, 5, &bruteforce_ui_task_handle);
}

void destroy_tasks() {
  if (polling_in_progress) {
    vTaskDelete(polling_task_handle);
    polling_task_handle = NULL;
  } else if (dump_in_progress) {
    vTaskDelete(dump_task_handle);
    dump_task_handle = NULL;
  } else if (format_in_progress) {
    vTaskDelete(format_task_handle);
    format_task_handle = NULL;
  } else if (bruteforce_in_progress) {
    vTaskDelete(bruteforce_task_handle);
    bruteforce_task_handle = NULL;
    vTaskDelete(bruteforce_ui_task_handle);
    bruteforce_ui_task_handle = NULL;
  }
}