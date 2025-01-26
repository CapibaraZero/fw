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

#ifndef NFC_ATTACKS_H
#define NFC_ATTACKS_H
#include <stdint.h>
#include "../../include/pins.h"
#include <cstddef>

typedef struct SectorResult {
  uint8_t uid[7];
  uint8_t uid_len = 0;
  bool key_a_found = false;
  uint8_t key_a[6];
  bool key_b_found = false;
  uint8_t key_b[6];
  bool dumped = false;
} SectorResult;

typedef struct EMVCard {
  bool parsed = true;
  uint8_t *aid = nullptr;
  size_t pan_len = 0;
  uint8_t *pan = nullptr;
  uint8_t *afl_raw = nullptr;
  uint8_t *validfrom = nullptr;
  uint8_t *validto = nullptr;
} EMVCard;

#include "NFCTag.hpp"
#include "nfc_framework.hpp"

class NFCAttacks {
 private:
  NFCFramework nfc_framework = NFCFramework(PN532_IRQ, PN532_RST);
  bool is_there_null_blocks(NFCTag *tag);
  NFCTag *current_tag = (NFCTag *)malloc(sizeof(NFCTag));
  uint8_t tried_keys = 0;
  uint8_t formatted_sectors = 0;
  uint8_t current_tag_blocks = 0;
  bool bruteforce_status = true;
  void auth_sector(uint8_t sector, uint8_t *key, KeyType key_type,
                   uint8_t *out_key, bool *key_found);
  bool read_sector(uint8_t initial_pos, uint8_t *key, KeyType key_type,
                   uint8_t *out);
                   
  // EMV methods created with the help of https://werner.rothschopf.net/201703_arduino_esp8266_nfc.htm
  void parse_pan(std::vector<uint8_t> *afl_content, EMVCard *card);
  void parse_validfrom(std::vector<uint8_t> *afl_content, EMVCard *card);
  void parse_validto(std::vector<uint8_t> *afl_content, EMVCard *card);
  void get_afl(EMVCard *card, uint8_t *afl);
 public:
  NFCAttacks(/* args */);
  ~NFCAttacks() {};
  bool begin();
  void power_down() {nfc_framework.power_down();};
  uint32_t get_version() {
    return nfc_framework.get_version();
  }
  bool bruteforce();
  void read_uid(uint8_t *uid, uint8_t *uid_length);
  void read_uid(uint8_t *uid, uint8_t *uid_length, uint16_t *atqa,
                uint8_t *sak);
  NFCTag dump_tag(DumpResult *result);
  NFCTag dump_tag(uint8_t *key, DumpResult *result);
  NFCTag dump_ntag(int pages);
  bool write_sector(uint8_t block_number, uint8_t *data, uint8_t key_type,
                    uint8_t *key);
  uint8_t write_ntag(NFCTag *tag);
  bool write_ntag(uint8_t page, uint8_t *data);
  uint8_t format_ntag(int pages);
  void format_tag();
  bool detect_felica(uint8_t *idm, uint8_t *pmm, uint16_t *sys_code);
  bool felica_read(uint8_t service_length, uint16_t *service_codes,
                   uint8_t num_blocks, uint16_t *block_list,
                   uint8_t data[][16]);
  int felica_read(uint8_t num_blocks, uint16_t *block_list, uint8_t data[][16]);
  int felica_write(NFCTag *tag);
  bool felica_write(uint8_t service_codes_list_length, uint16_t *service_codes,
                    uint8_t block_number, uint16_t *block_list,
                    uint8_t data[][16]);
  int felica_write(uint8_t block_number, uint16_t *block_list,
                   uint8_t data[][16]);
  uint8_t felica_format(uint8_t blocks);
  uint8_t felica_dump(int blocks, uint8_t data[][16]);
  NFCTag felica_dump(int blocks, uint8_t *unreadable);
  bool felica_clone(NFCTag *tag);
  void printHex(uint8_t *payload) {
    nfc_framework.printHex(payload, sizeof(payload) / sizeof(payload[0]));
  }
  void printHex(uint8_t *payload, size_t size) {
    nfc_framework.printHex(payload, size);
  }

  void set_scanned_tag(NFCTag *tag) { memcpy(current_tag, tag, sizeof(tag)); };
  NFCTag *get_scanned_tag() { return current_tag; };
  NFCTag get_tag_towrite(uint8_t uid_length);
  NFCTag get_felica_towrite();
  uint8_t get_tried_keys() { return tried_keys; };
  bool get_bruteforce_status() { return bruteforce_status; };
  uint8_t get_formatted_sectors() { return formatted_sectors; };
  uint8_t get_tag_blocks() { return current_tag_blocks; };

  bool emulate_tag(uint8_t *uid);
  bool emulate_tag(uint8_t *idm, uint8_t *pmm, uint8_t *sys_code);

  // EMV methods created with the help of https://werner.rothschopf.net/201703_arduino_esp8266_nfc.htm
  EMVCard read_emv_card();
};

#endif
