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

#include "nfc_attacks.hpp"
#include "posixsd.hpp"
#include <algorithm>
#include <list>
#include <vector>
#include "fm.hpp"
#include "helper.hpp"
#include "../../include/debug.h"

using namespace std;

#define NFC_KEYS_FILE "/NFC/keys.txt"

NFCAttacks::NFCAttacks()
{
    if (!nfc_framework.ready())
    {
        LOG_ERROR("PN532 not found, trying to restart\n");
    }
    else
    {
        LOG_SUCCESS("PN532 found!\n");
    }
}
bool NFCAttacks::is_there_null_blocks(NFCTag *tag)
{
    for (size_t i = 0; i < tag->get_blocks_count(); i++)
    {
        uint8_t block[BLOCK_SIZE] = {0};
        tag->get_block(i, block);
        for (size_t j = 0; j < 16; j++)
        {
            if (block[j] == -1)
            {
                return true;
            }
        }
    }
    return false;
}

void NFCAttacks::bruteforce()
{
    File keys = open(NFC_KEYS_FILE, "r");
    if (keys.available())
    {
        LOG_INFO("File found!\n");
        vector<String> lines = readlines(keys); // Read all lines
        size_t key_index = 0;                   // Index for the current key in keys
        for (String line : lines)
        {
            vector<String> raw_key = string_split((char *)line.c_str(), " "); // String string for each space
            uint8_t parsed_key[6];
            size_t i = 0; // byte index counter
            for (auto key_byte : raw_key)
            {
                parsed_key[i++] = strtol(key_byte.c_str(), NULL, 16); // Convert hex to uint8_t
                SERIAL_DEVICE.printf("%s\n", key_byte.c_str());
            }

            uint8_t *uid;
            uint8_t *uid_length;

            while (!nfc_framework.get_tag_uid(uid, uid_length))
            {
                __asm__ __volatile__("nop\n\t");
            };

            LOG_INFO("Found a new tag!\n");
            LOG_INFO("Tag UID: ");
            printHex(uid);
            NFCTag tag = dump_tag(parsed_key);
            if (!is_there_null_blocks(&tag))
            {
                LOG_SUCCESS("Key found!");
                return;
            }
            key_index++; // Go to next key
        }
    }
    else
    {
        LOG_ERROR("Keys file not found.\n");
    }
}

void NFCAttacks::read_uid(uint8_t *uid, uint8_t *uid_length)
{
    if (!nfc_framework.get_tag_uid(uid, uid_length))
    {
        uid = NULL;
        uid_length = NULL;
    };
}

NFCTag NFCAttacks::dump_tag()
{
    uint8_t key_universal[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Universal key
    size_t key_length;
    return NFCTag(nfc_framework.dump_tag(key_universal, &key_length), key_length); // uint8_t to NFCTag object
}

NFCTag NFCAttacks::dump_tag(uint8_t *key)
{
    size_t key_length;
    return NFCTag(nfc_framework.dump_tag(key, &key_length), key_length); // uint8_t to NFCTag object
}

NFCTag NFCAttacks::dump_ntag(int pages)
{
    return NFCTag(nfc_framework.dump_ntag2xx_tag(pages), 7, pages);
}

void NFCAttacks::write_tag(NFCTag *tag)
{
    uint8_t key_universal[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Universal key
    for (size_t i = 0; i < tag->get_blocks_count(); i++)
    {
        Serial0.printf("Writing block: %i\n", i);
        uint8_t block[BLOCK_SIZE] = {0};
        tag->get_block(i, block);
        if (nfc_framework.write_tag(i, block, key_universal))
        {
            LOG_SUCCESS("Block written correctly\n");
        }
        else
        {
            LOG_ERROR("Error during writing block.");
        };
    }
}

void NFCAttacks::write_tag(NFCTag *tag, uint8_t *key)
{
    for (size_t i = 0; i < tag->get_blocks_count(); i++)
    {
        Serial0.printf("Writing block: %i\n", i);
        uint8_t block[BLOCK_SIZE] = {0};
        tag->get_block(i, block);
        if (nfc_framework.write_tag(i, block, key))
        {
            LOG_SUCCESS("Block written correctly\n");
        }
        else
        {
            LOG_ERROR("Error during writing block.");
        };
    }
}

void NFCAttacks::write_ntag(NFCTag *tag)
{
    const size_t tag_size = tag->get_blocks_count();
    const size_t reserved_pages = tag_size == NTAG203_PAGES ? NTAG203_RESERVED_PAGES : NTAG21X_RESERVED_PAGES;

    /* Skip non-user sectors since it's not writable */
    for (size_t i = 4; i != tag_size - reserved_pages; i++)
    {
        Serial0.printf("Writing block: %i\n", i);
        uint8_t block[4];
        tag->get_block(i, block);
        if (nfc_framework.write_ntag2xx_page(i, block))
        {
            LOG_SUCCESS("Block written correctly\n");
        }
        else
        {
            LOG_ERROR("Error during writing block.\n");
        };
    }
}