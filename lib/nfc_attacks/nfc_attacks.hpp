/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or https://capibarazero.github.io/).
 * Copyright (c) 2023 Andrea Canale.
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

#include "nfc_framework.hpp"
#include "NFCTag.hpp"

class NFCAttacks
{
private:
    NFCFramework nfc_framework = NFCFramework();
    bool is_there_null_blocks(NFCTag *tag);
    // For internal usage(format)
    uint8_t write_tag(NFCTag *tag, int starting_block);
    void write_tag(NFCTag *tag, uint8_t *key, int starting_key);
    NFCTag *current_tag = (NFCTag *)malloc(sizeof(NFCTag));
    uint8_t tried_keys = 0;
    bool bruteforce_status = true;
public:
    NFCAttacks(/* args */);
    ~NFCAttacks() {};
    bool bruteforce();
    void read_uid(uint8_t *uid, uint8_t *uid_length);
    NFCTag dump_tag(DumpResult *result);
    NFCTag dump_tag(uint8_t *key, DumpResult *result);
    NFCTag dump_ntag(int pages);
    uint8_t write_tag(NFCTag *tag);
    void write_tag(NFCTag *tag, uint8_t *key);
    uint8_t format_tag(bool ultralight = false);
    void format_tag(uint8_t *key, bool ultralight = false);
    uint8_t write_ntag(NFCTag *tag);
    uint8_t format_ntag(int pages);
    bool detect_felica(uint8_t *idm, uint8_t *pmm, uint16_t *sys_code);
    bool felica_read(uint8_t service_length, uint16_t *service_codes, uint8_t num_blocks, 
                            uint16_t *block_list, uint8_t data[][16]);
    bool felica_read(uint8_t num_blocks, uint16_t *block_list, uint8_t data[][16]);
    bool felica_write(uint8_t service_codes_list_length, uint16_t *service_codes, 
                            uint8_t block_number, uint16_t *block_list, uint8_t data[][16]);
    bool felica_write(uint8_t block_number, uint16_t *block_list, uint8_t data[][16]);
    void printHex(uint8_t *payload) { nfc_framework.printHex(payload, sizeof(payload) / sizeof(payload[0])); }
    void printHex(uint8_t *payload, size_t size) { nfc_framework.printHex(payload, size); }

    void set_scanned_tag(NFCTag *tag) {
        memcpy(current_tag, tag, sizeof(tag));
    };
    NFCTag *get_scanned_tag() { return current_tag; };
    NFCTag get_tag_towrite(uint8_t uid_length);
    uint8_t get_tried_keys() { return tried_keys; };
    bool get_bruteforce_status() { return bruteforce_status; };
};

#endif
