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

// This file contains implementation of functions that starts wifiAttack on
// button click

#include <Arduino.h>

#include "../../include/debug.h"
#include "../UI/gui.hpp"
#include "../UI/navigation/wifi/wifi_navigation.hpp"
#include "GFXForms.hpp"  // Fix building errors
#include "ui_tasks/wifi/wifi_ui_tasks.hpp"
#include "ui_tasks/wifi/wifi_ui_tasks_types.h"
#include "wifi_sniff_task_types.h"
#include "wifi_tasks.hpp"

#define TASK_STACK_SIZE 16000

WiFiUITaskParameters *wifi_ui_task_params = NULL;

void scan_wifi(Gui *gui, WifiAttack *wifiAttack) {
  /* We delete this after usage, so we need to recreate struct every time */
  wifi_ui_task_params =
      (WiFiUITaskParameters *)malloc(sizeof(WiFiUITaskParameters));
  wifi_ui_task_params->wifi_attack = wifiAttack;
  wifi_ui_task_params->gui = gui;
  xTaskCreate(&wifi_scan_task, "wifi_scan", TASK_STACK_SIZE, (void *)wifiAttack,
              5, NULL);
  xTaskCreate(&update_wifi_scan_progress, "wifi_scan_gui_updater", 4000,
              (void *)wifi_ui_task_params, tskIDLE_PRIORITY, NULL);
}

#define SNIFF_TASK_SIZE 4000  // Estimated using uxTaskGetStackHighWaterMark()
TaskHandle_t wifi_sniffer_updater = NULL;

void sniff_wifi(Gui *gui, WifiAttack *wifiAttack) {
  gui->reset();
  show_wifi_sniff_page();
  xTaskCreate(&wifi_sniff_task, "wifi_sniff", SNIFF_TASK_SIZE,
              (void *)wifiAttack, 5, NULL);
  while (!wifiAttack->sniffer_running()) {
    delay(1);  // Wait for sniffer initialization
  }
  /* We delete this after usage, so we need to recreate struct every time */
  wifi_ui_task_params =
      (WiFiUITaskParameters *)malloc(sizeof(WiFiUITaskParameters));
  wifi_ui_task_params->wifi_attack = wifiAttack;
  wifi_ui_task_params->gui = gui;
  xTaskCreate(&update_wifi_sniff_packets, "update_wifi_sniff", 3000,
              (void *)wifi_ui_task_params, tskIDLE_PRIORITY,
              &wifi_sniffer_updater);
}

void stop_wifi_sniffer_updater() {
  while (get_sniffer_lock()) {
    /* Wait until GUI is updated to avoid graphical glitches */
    NOP();
  }
  vTaskDelete(wifi_sniffer_updater);
  wifi_sniffer_updater = NULL;
}

BSSIDSniff bssid_sniff;

void sniff_bssid(Gui *gui, WifiAttack *wifiAttack) {
  LOG_INFO(get_current_network().get_ssid());
  bssid_sniff.attack = wifiAttack;
  bssid_sniff.ch = get_current_network().get_channel();
  bssid_sniff.bssid = get_current_network().get_bssid();
  xTaskCreate(&wifi_sniff_bssid, "wifi_sniff_bssid", 4000, (void *)&bssid_sniff,
              5, NULL);
  while (!wifiAttack->sniffer_running()) {
    delay(1);  // Wait for sniffer initialization
  }
  /* We delete this after usage, so we need to recreate struct every time */
  wifi_ui_task_params =
      (WiFiUITaskParameters *)malloc(sizeof(WiFiUITaskParameters));
  wifi_ui_task_params->wifi_attack = wifiAttack;
  wifi_ui_task_params->gui = gui;
  xTaskCreate(&update_wifi_sniff_packets, "update_wifi_sniff", 3000,
              (void *)wifi_ui_task_params, tskIDLE_PRIORITY,
              &wifi_sniffer_updater);
}

void return_to_net_list(Gui *gui) {}
