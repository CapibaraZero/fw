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

#include "duktape.h"
#include "NimBLEDevice.h"
#include "bluetooth_attacks.hpp"
#include "posixsd.hpp"

extern void generateRandomMac(uint8_t *mac);
static BluetoothAttack *ble_attack = new BluetoothAttack();
TaskHandle_t ble_task_handle = nullptr;

duk_ret_t init_ble_js() {
    uint8_t macAddr[6];
    generateRandomMac(macAddr);

    esp_base_mac_addr_set(macAddr);

    NimBLEDevice::init("");
    return 0;
}

void apple_juice_task(void *pv) {
    ble_attack->appleJuiceAttack();
}

void fast_pair_task(void *pv) {
    ble_attack->fastPairSpamAttack();
}

void swift_pair_task(void *pv) {
    ble_attack->swiftPairSpamAttack();
}

duk_ret_t start_applejuice(duk_context *ctx) {
    xTaskCreate(apple_juice_task, "apple_juice_task", 1500, NULL, 5, &ble_task_handle);
    return 0;
}

duk_ret_t stop_applejuice(duk_context *ctx) {
    vTaskDelete(ble_task_handle);
    ble_attack->kill_applejuice();
    return 0;
}

duk_ret_t start_fastpair(duk_context *ctx) {
    xTaskCreate(fast_pair_task, "fast_pair_task", 1500, NULL, 5, &ble_task_handle);
    return 0;
}

duk_ret_t stop_fastpair(duk_context *ctx) {
    vTaskDelete(ble_task_handle);
    ble_attack->kill_fast_pair_spam();
    return 0;
}

duk_ret_t start_swift_pair(duk_context *ctx) {
    xTaskCreate(swift_pair_task, "swift_pair_task", 1500, NULL, 5, &ble_task_handle);
    return 0;
}

duk_ret_t stop_swift_pair(duk_context *ctx) {
    vTaskDelete(ble_task_handle);
    ble_attack->kill_swift_pair_spam();
    return 0;
}

duk_ret_t sniff_ble(duk_context *ctx) {
    ble_attack->sniff(get_current_fs());
    return 0;
} 

duk_ret_t randomize_mac_addr(duk_context *ctx) {
    NimBLEDevice::deinit(true);
    uint8_t macAddr[6];
    generateRandomMac(macAddr);

    esp_base_mac_addr_set(macAddr);

    // NimBLEDevice::init("");
    NimBLEDevice::init("");
    return 0;
}

duk_ret_t advertise(duk_context *ctx) {
    // TODO
    return 0;
}

void init_js_ble(duk_context *ctx) {
    duk_push_c_function(ctx, start_applejuice, 0);
    duk_put_global_string(ctx, "start_applejuice");
    duk_push_c_function(ctx, start_fastpair, 0);
    duk_put_global_string(ctx, "start_fastpair");
    duk_push_c_function(ctx, start_swift_pair, 0);
    duk_put_global_string(ctx, "start_swift_pair");
    duk_push_c_function(ctx, sniff_ble, 0);
    duk_put_global_string(ctx, "sniff_ble");
    duk_push_c_function(ctx, randomize_mac_addr, 0);
    duk_put_global_string(ctx, "ble_randomize_mac_addr");
}