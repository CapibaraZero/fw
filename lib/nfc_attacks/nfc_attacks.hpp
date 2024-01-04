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
public:
    NFCAttacks(/* args */);
    inline ~NFCAttacks() {};
    void bruteforce();
    void read_uid(uint8_t *uid, uint8_t *uid_length);
    NFCTag dump_tag();
    NFCTag dump_tag(uint8_t *key);
    NFCTag dump_ntag(int pages);
    void write_tag(NFCTag *tag);
    void write_tag(NFCTag *tag, uint8_t *key);
    void write_ntag(NFCTag *tag);
    void printHex(uint8_t *payload) { nfc_framework.printHex(payload, sizeof(payload) / sizeof(payload[0])); }
};

#endif