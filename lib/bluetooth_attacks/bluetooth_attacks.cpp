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

#include "bluetooth_attacks.hpp"

#include "../../include/pcap_gen.h"

#define PCAP_TYPE String("bluetooth")

void BluetoothAttack::sniff(FS sd) {
  sniffer = new BLESniffer(PCAP_FILE(PCAP_TYPE).c_str());
  sniffer->sniff(sd);
}

void BluetoothAttack::scan(FS sd, int scan_time) {
  scanner = new BLEScanner(scan_time);
  sc_time = scan_time;
  delay(scan_time + 1000);  // Scan time + about 1 sec for BLE stack
                            // initialization time, ecc...
  while (scanner->is_scanning()) {
    /* If scan still in progress do nothing */
    __asm__ __volatile__("nop\n\t");
  }

  scanner->save_to_sd(sd, scanner->get_result());
}
