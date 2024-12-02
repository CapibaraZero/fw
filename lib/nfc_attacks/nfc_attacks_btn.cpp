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
}