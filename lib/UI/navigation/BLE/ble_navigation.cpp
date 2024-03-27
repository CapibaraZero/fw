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
#include "NimBLEDevice.h"
#include "ble_attacks_btn.hpp"
#include "bluetooth_attacks.hpp"
#include "gui.hpp"
#include "debug.h"

#define BLE_DEVICE_NAME "capibaraZero"

static Gui *gui;
static BluetoothAttack *attack = new BluetoothAttack();

void goto_ble_gui() {
  gui->reset();
  gui->set_current_position(0);
  gui->init_ble_gui();
}

/* void goto_ble_scan_gui() {
    gui->reset();
    gui->set_current_position(0);
    gui->init_ble_scan_gui();
    scan_ble(gui, attack, get_current_fs());
} */

void goto_ble_sniff_gui() {
  gui->reset();
  gui->set_current_position(0);
  gui->init_ble_sniff_gui();
  sniff_ble(gui, attack);
}

void init_spam_gui() {
  gui->reset();
  gui->set_current_position(0);
  gui->init_ble_spam_gui();
}

void goto_applejuice() {
  init_spam_gui();
  start_applejuice(attack);
}

void goto_samsung_spam() { init_spam_gui(); }

void goto_swift_spam() { init_spam_gui(); }

void ble_submenu_handler(int pos) {
  LOG_INFO("Here");
  Serial.printf("BLE POS: %i", pos);
  switch (pos) {
    case 0:  // Start scan
      LOG_INFO("Start sniff");
      gui->ok(goto_ble_sniff_gui);
      break;
    case 1:  // Start spam
      gui->ok(goto_applejuice);
      break;
    case 2:
      gui->ok(goto_samsung_spam);
      break;
    case 3:
      gui->ok(goto_swift_spam);
      break;
    default:
      break;
  }
}

void stop_ble_sniffer() {
#ifdef CONFIG_DEBUG_WIFI_MENU
  LOG_INFO("Sniff menu");
#endif
  /* Stop sniffer */
  attack->stop_sniff();
  /* if(wifiAttack.get_networks().size() > 0)
     wifiAttack.clean_networks(); */
  gui->destroy_ble_sniff_gui();
  init_main_gui();
  NimBLEDevice::deinit();  // Save some resources
}

void stop_applejuice() {
  kill_applejuice_task();
  attack->kill_applejuice();
}

void stop_samsung_ble_spam() {
  kill_samsung_ble_spam();
  attack->kill_samsung_ble_spam();
}

void stop_swift_pair_spam() {
  kill_swift_pair_spam();
  attack->kill_swift_pair_spam();
}

void handle_ble_spam_stop() {
  if (attack->appleJuice_running())
    stop_applejuice();
  else if (attack->samsung_ble_spam_running())
    stop_samsung_ble_spam();
  else if (attack->swift_pair_spam_running())
    stop_swift_pair_spam();

  NimBLEDevice::deinit();
  gui->destroy_ble_spam_gui();
  init_main_gui();
}

void init_ble_navigation(Gui *_gui) {
  LOG_INFO("Init BLE Navigation");
  gui = _gui;
  NimBLEDevice::init(BLE_DEVICE_NAME);
}
