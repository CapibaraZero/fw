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
#include "../navigation.hpp"
#include "NimBLEDevice.h"
#include "ble_attacks_btn.hpp"
#include "bluetooth_attacks.hpp"
#include "gui.hpp"
#include "pages/BLE/BLEPage.hpp"
#include "pages/BLE/BLEScanPage.hpp"
#include "pages/BLE/BLESniffPage.hpp"
#include "pages/BLE/BLESpamPage.hpp"

#define BLE_DEVICE_NAME "capibaraZero"

static Gui *gui;
static BluetoothAttack *attack = new BluetoothAttack();
static BLEPage *ble_page;
static BLESniffPage *ble_sniffer_page;
static BLESpamPage *ble_spam_page;

void goto_ble_gui() {
  gui->reset();
  ble_page = new BLEPage(5, 0, 1, gui->get_screen());
  gui->set_current_page(ble_page);
}

void goto_ble_sniff_gui() {
  gui->reset();
  ble_sniffer_page = new BLESniffPage(0, 0, 0, gui->get_screen());
  gui->set_current_page(ble_sniffer_page);
  sniff_ble(gui, attack);
}

void init_spam_gui() {
  gui->reset();
  ble_spam_page = new BLESpamPage(0, 0, 0, gui->get_screen());
  gui->set_current_page(ble_spam_page);
}

// void set_ble_adv_devices_text(int adv_devices) {
//     ble_scan_page->set_adv_devices_text(String(adv_devices).c_str());
// }
// void set_ble_progress(char *progress) {
//     ble_scan_page->update_progress(progress);
// };
void update_ble_packets_count(int count) {
  if (ble_sniffer_page != nullptr) ble_sniffer_page->update_packet_count(count);
};

void goto_applejuice() {
  init_spam_gui();
  start_applejuice(attack);
}

void goto_samsung_spam() {
  init_spam_gui();
  start_samsung_ble_spam(attack);
}

void goto_swift_spam() {
  init_spam_gui();
  start_swift_pair_spam(attack);
}

void goto_fastpair_spam() {
  init_spam_gui();
  start_fast_pair_spam(attack);
}

void ble_goto_home() {
  init_main_gui();
  ble_page = nullptr;
}

void stop_ble_sniffer() {
#ifdef CONFIG_DEBUG_WIFI_MENU
  LOG_INFO("Sniff menu");
#endif
  /* Stop sniffer */
  attack->stop_sniff();
  stop_sniffer_updater();
  init_main_gui();
  ble_sniffer_page = nullptr;
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

void stop_fast_pair_spam() {
  kill_fast_pair_spam();
  attack->kill_fast_pair_spam();
}

void handle_ble_spam_stop() {
  if (attack->appleJuice_running())
    stop_applejuice();
  else if (attack->samsung_ble_spam_running())
    stop_samsung_ble_spam();
  else if (attack->swift_pair_spam_running())
    stop_swift_pair_spam();
  else if (attack->fast_pair_spam_running())
    stop_fast_pair_spam();
  NimBLEDevice::deinit();
  init_main_gui();
  ble_spam_page = nullptr;
}

// From
// https://github.com/Spooks4576/ESP32Marauder/blob/c8005f6c52e565c74e619924da851728e734f0b4/esp32_marauder/WiFiScan.cpp#L1641
void generateRandomMac(uint8_t *mac) {
  // Set the locally administered bit and unicast bit for the first byte
  mac[0] = 0x02;  // The locally administered bit is the second least
                  // significant bit

  // Generate the rest of the MAC address
  for (int i = 1; i < 6; i++) {
    mac[i] = random(0, 255);
  }
}

void init_ble_navigation(Gui *_gui) {
  LOG_INFO("Init BLE Navigation");
  gui = _gui;
  uint8_t macAddr[6];
  generateRandomMac(macAddr);

  esp_base_mac_addr_set(macAddr);

  // NimBLEDevice::init("");
  NimBLEDevice::init("");
}
