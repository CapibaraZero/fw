/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2023 Andrea Canale.
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

#ifndef BLUETOOTHATTACKS_H
#define BLUETOOTHATTACKS_H

#include "AppleJuice.hpp"
#include "BLEScanner.hpp"
#include "BLESniffer.hpp"
#include "FS.h"
#include "fast_pair_spam.hpp"
#include "microsoft_ble_spam.hpp"
#include "samsung_ble_spam.hpp"

class BluetoothAttack {
 private:
  AppleJuice *appleJuice = nullptr;
  SamsungBleSpam *samsung_ble_spam = nullptr;
  MicrosoftBleSpam *swift_pair_spam = nullptr;
  FastPairSpam *fast_pair_spam = nullptr;
  BLEScanner *scanner;
  BLESniffer *sniffer;
  int sc_time = 15000;

 public:
  BluetoothAttack() {};
  ~BluetoothAttack() {};
  void appleJuiceAttack() {
    appleJuice = new AppleJuice();
    for (;;) {
      appleJuice->attack();
    }
  };
  void samsungBleSpamAttack() {
    samsung_ble_spam = new SamsungBleSpam();
    for (;;) {
      samsung_ble_spam->attack();
    }
  };
  void swiftPairSpamAttack() {
    swift_pair_spam = new MicrosoftBleSpam();
    for (;;) {
      swift_pair_spam->attack();
    }
  };

  void fastPairSpamAttack() {
    fast_pair_spam = new FastPairSpam();
    for (;;) {
      fast_pair_spam->attack();
    }
  };
  void kill_applejuice() {
    delete appleJuice;
    appleJuice = nullptr;
  }

  void kill_samsung_ble_spam() {
    delete samsung_ble_spam;
    samsung_ble_spam = nullptr;
  }

  void kill_swift_pair_spam() {
    delete swift_pair_spam;
    swift_pair_spam = nullptr;
  }

  void kill_fast_pair_spam() {
    delete fast_pair_spam;
    fast_pair_spam = nullptr;
  }

  bool appleJuice_running() { return appleJuice != nullptr; };
  bool samsung_ble_spam_running() { return samsung_ble_spam != nullptr; };
  bool swift_pair_spam_running() { return swift_pair_spam != nullptr; };
  bool fast_pair_spam_running() { return fast_pair_spam != nullptr; };

  void sniff(FS sd);
  void stop_sniff() { sniffer->stop(); };

  void scan(FS sd, int scan_time = 15000);
  uint8_t get_scanned_devices() { return scanner->get_scanned_devices(); };
  bool is_scanning() { return scanner->is_scanning(); };
  int get_scanning_time() { return sc_time; };
  void set_scanning_time(int scan_time) { sc_time = scan_time; };

  bool is_sniffing() { return sniffer->is_sniffing(); };
  int get_sniffed_packets() { return sniffer->get_sniffed_packets(); };
};

#endif
