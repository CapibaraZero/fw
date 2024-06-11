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

static void ble_goto_home() {
    gui->destroy_ble_gui();
    init_main_gui();
}
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
        case 4:
            gui->ok(goto_fastpair_spam);
            break;
        case 5:
            gui->ok(ble_goto_home);
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
    stop_sniffer_updater();
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
    else if(attack->fast_pair_spam_running())
        stop_fast_pair_spam();
    NimBLEDevice::deinit();
    gui->destroy_ble_spam_gui();
    init_main_gui();
}

// From https://github.com/Spooks4576/ESP32Marauder/blob/c8005f6c52e565c74e619924da851728e734f0b4/esp32_marauder/WiFiScan.cpp#L1641
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
