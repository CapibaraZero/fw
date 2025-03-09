#include "lvgl.h"
#include "ui.h"
#include "vars.h"
#include "bluetooth_attacks.hpp"
#include "ble_attacks_btn.hpp"

static BluetoothAttack *attack = new BluetoothAttack();

bool applejuice_running = false;
bool fastpair_running = false;
bool swiftpair_running = false;

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

extern "C" void action_go_to_ble_page(lv_event_t *e) {
    create_screen_ble_page();
    loadScreen(SCREEN_ID_BLE_PAGE);

    uint8_t macAddr[6];
    generateRandomMac(macAddr);
  
    esp_base_mac_addr_set(macAddr);
  
    NimBLEDevice::init("");
}

extern "C" void action_start_ble_sniffer(lv_event_t *e) {
    create_screen_sniffer();
    loadScreen(SCREEN_ID_SNIFFER);
    sniff_ble(attack);
}

void stop_ble_sniffer() {
    attack->stop_sniff();
    stop_sniffer_updater();

    NimBLEDevice::deinit();
}

extern "C" void action_start_ble_spam(lv_event_t *e) {
    create_screen_ble_spam();
    loadScreen(SCREEN_ID_BLE_SPAM);

    int mode = (int)e->user_data;
    Serial.println(mode);
    
    if(mode == 0) {
        applejuice_running = true;
        start_applejuice(attack);
    } else if(mode == 1) {
        fastpair_running = true;
        start_fast_pair_spam(attack);
    } else if(mode == 2) {
        swiftpair_running = true;
        start_swift_pair_spam(attack);
    }
}

extern "C" void action_stop_ble_spam(lv_event_t *e) {
    int mode = (int)e->user_data;

    if(applejuice_running) {
        applejuice_running = false;
        kill_applejuice_task();
        attack->kill_applejuice();
    } else if(fastpair_running) {
        fastpair_running = false;
        kill_fast_pair_spam();
        attack->kill_fast_pair_spam();
    } else if(swiftpair_running) {
        swiftpair_running = false;
        kill_swift_pair_spam();
        attack->kill_swift_pair_spam();
    }

    create_screen_main();
    loadScreen(SCREEN_ID_MAIN);
    NimBLEDevice::deinit();
}
