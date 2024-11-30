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

#include "../../include/debug.h"
#include "GFXForms.hpp"  // Fix building errors
#include "ble_attack_tasks.hpp"
#include "bluetooth_attacks.hpp"
#include "gui.hpp"
#include "posixsd.hpp"
#include "ui_tasks/BLE/ble_ui_tasks.hpp"
#include "ui_tasks/BLE/ble_ui_tasks_types.h"
#include "wifi_attack.hpp"  // Fix building errors. TODO: Try to remove it

#define TASK_STACK_SIZE 4000  // Calculated with uxTaskGetStackHighWaterMark()
#define SPAM_TASK_STACK_SIZE \
  1500  // Spam task use less memory than sniff. Calculated with
        // uxTaskGetStackHighWaterMark()

BLEUITaskParameters *ble_ui_task_params = NULL;

static TaskHandle_t applejuice_handle = NULL;
static TaskHandle_t samsung_ble_spam_handle = NULL;
static TaskHandle_t swift_pair_spam_handle = NULL;
static TaskHandle_t fast_pair_spam_handle = NULL;

void scan_ble(Gui *gui, BluetoothAttack *attack) {
  LOG_INFO("Start scanning BLE");
  /* We delete this after usage, so we need to recreate struct every time */
  ble_ui_task_params =
      (BLEUITaskParameters *)malloc(sizeof(BLEUITaskParameters));
  ble_ui_task_params->ble_attack = attack;
  ble_ui_task_params->gui = gui;
  xTaskCreate(&ble_scan_task, "ble_scan", TASK_STACK_SIZE,
              (void *)ble_ui_task_params, 5, NULL);
  xTaskCreate(&update_ble_scan_progress, "ble_scan_gui_updater", 4000,
              (void *)ble_ui_task_params, tskIDLE_PRIORITY, NULL);
}

TaskHandle_t ble_sniffer_updater = NULL;

void sniff_ble(Gui *gui, BluetoothAttack *attack) {
  /* We delete this after usage, so we need to recreate struct every time */
  ble_ui_task_params =
      (BLEUITaskParameters *)malloc(sizeof(BLEUITaskParameters));
  ble_ui_task_params->ble_attack = attack;
  ble_ui_task_params->gui = gui;
  xTaskCreate(&ble_sniff_task, "ble_sniff", TASK_STACK_SIZE,
              (void *)ble_ui_task_params, 5, NULL);
  xTaskCreate(&update_ble_sniffed_packets, "ble_sniff_gui_updater", 4000,
              (void *)ble_ui_task_params, tskIDLE_PRIORITY,
              &ble_sniffer_updater);
}

void stop_sniffer_updater() { vTaskDelete(ble_sniffer_updater); }

void start_applejuice(BluetoothAttack *attack) {
  xTaskCreate(&applejuice_task, "applejuice_task", SPAM_TASK_STACK_SIZE,
              (void *)attack, 5, &applejuice_handle);
};

void kill_applejuice_task() { vTaskDelete(applejuice_handle); };

void start_samsung_ble_spam(BluetoothAttack *attack) {
  xTaskCreate(&samsung_ble_spam_task, "samsung_ble_spam_task",
              SPAM_TASK_STACK_SIZE, (void *)attack, 5,
              &samsung_ble_spam_handle);
}

void kill_samsung_ble_spam() { vTaskDelete(samsung_ble_spam_handle); }

void start_swift_pair_spam(BluetoothAttack *attack) {
  xTaskCreate(&swift_pair_spam_task, "swift_pair_spam_task",
              SPAM_TASK_STACK_SIZE, (void *)attack, 5, &swift_pair_spam_handle);
}

void kill_swift_pair_spam() { vTaskDelete(swift_pair_spam_handle); }

void start_fast_pair_spam(BluetoothAttack *attack) {
  xTaskCreate(&fast_pair_spam_task, "fast_pair_spam_task", SPAM_TASK_STACK_SIZE,
              (void *)attack, 5, &fast_pair_spam_handle);
}

void kill_fast_pair_spam() { vTaskDelete(fast_pair_spam_handle); }