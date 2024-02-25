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
#include "ArduinoJson.h"

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

bool NFCAttacks::bruteforce()
{
    bruteforce_status = true;
    File keys = open(NFC_KEYS_FILE, "r");
    if (keys.available())
    {
        LOG_INFO("File found!\n");
        vector<String> lines = readlines(keys); // Read all lines
        size_t key_index = 0;                   // Index for the current key in keys
        for (String line : lines)
        {
            if(line[0] == '#')  // If is a comment, skip
                continue;
            vector<String> raw_key = string_split((char *)line.c_str(), " "); // String string for each space
            uint8_t parsed_key[6];
            size_t i = 0; // byte index counter
            for (auto key_byte : raw_key)
            {
                parsed_key[i++] = strtol(key_byte.c_str(), NULL, 16); // Convert hex to uint8_t
                SERIAL_DEVICE.printf("%s\n", key_byte.c_str());
            }

            uint8_t uid[7];
            uint8_t uid_length;

            nfc_framework.get_tag_uid(uid, &uid_length);

            LOG_INFO("Found a new tag!\n");
            LOG_INFO("Tag UID: ");
            nfc_framework.printHex(uid, 7);

            tried_keys++;   // For statistics use
            DumpResult dump_result;
            NFCTag tag = dump_tag(parsed_key, &dump_result);
            if (dump_result.unauthenticated == 0)
            {
                LOG_SUCCESS("Key found!");
                bruteforce_status = false;
                return true;
            }
            key_index++; // Go to next key
        }
    }
    else
    {
        LOG_ERROR("Keys file not found.\n");
    }
    bruteforce_status = false;
    return false;
}

void NFCAttacks::read_uid(uint8_t *uid, uint8_t *uid_length)
{
    Serial0.println("Read UID: ");
    if (!nfc_framework.get_tag_uid(uid, uid_length))
    {
        uid = NULL;
        uid_length = NULL;
    };
}
NFCTag NFCAttacks::dump_tag(DumpResult *result)
{
    uint8_t key_universal[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Universal key
    size_t key_length;
    uint8_t *data = nfc_framework.dump_tag(key_universal, &key_length, result);
    if(key_length == 4)
        return NFCTag(data, key_length); // uint8_t to NFCTag object
    else 
        return NFCTag(data, key_length, NTAG213_PAGES); // uint8_t to NFCTag object
}

NFCTag NFCAttacks::dump_tag(uint8_t *key, DumpResult *result)
{
    size_t key_length;
    return NFCTag(nfc_framework.dump_tag(key, &key_length, result), key_length); // uint8_t to NFCTag object
}

NFCTag NFCAttacks::dump_ntag(int pages)
{
    return NFCTag(nfc_framework.dump_ntag2xx_tag(pages), 7, pages);
}

uint8_t NFCAttacks::write_tag(NFCTag *tag)
{
    uint8_t key_universal[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Universal key
    uint8_t unwritable = 0;
    uint8_t uid[7];
    uint8_t uid_length;
    if(nfc_framework.get_tag_uid(uid, uid_length)) {
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
                unwritable++;
                LOG_ERROR("Error during writing block.");
            };
        }
    } else {
        Serial0.println("Unable to find card");
    }
    return unwritable;
}

uint8_t NFCAttacks::write_tag(NFCTag *tag, int starting_block)
{
    uint8_t key_universal[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Universal key
    uint8_t unwritable = 0;
    uint8_t uid[7];
    uint8_t uid_length;
    // Avoid crashing if no card is present
    if(nfc_framework.get_tag_uid(uid, uid_length)) {
        for (size_t i = starting_block; i < tag->get_blocks_count(); i++)
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
    } else {
        Serial0.println("Unable to find card");
    }
    return unwritable;
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

void NFCAttacks::write_tag(NFCTag *tag, uint8_t *key, int starting_block)
{
    for (size_t i = starting_block; i < tag->get_blocks_count(); i++)
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

uint8_t NFCAttacks::format_tag(bool ultralight)
{
    LOG_INFO("Formatting tag...");
    uint8_t empty_tag_data[ultralight ? MIFARE_ULTRALIGHT_SIZE : MIFARE_CLASSIC_SIZE] = {0};
    NFCTag empty_tag = NFCTag(empty_tag_data, 4);   // Uid lenght is dummy here since it's an empty key
    return write_tag(&empty_tag, ultralight ? 7 : 4);
}

void NFCAttacks::format_tag(uint8_t *key ,bool ultralight)
{
    LOG_INFO("Formatting tag...");
    uint8_t empty_tag_data[ultralight ? MIFARE_ULTRALIGHT_SIZE : MIFARE_CLASSIC_SIZE] = {0};
    NFCTag empty_tag = NFCTag(empty_tag_data, 4);   // Uid lenght is dummy here since it's an empty key
    write_tag(&empty_tag, key, ultralight ? 7 : 4);
}


uint8_t NFCAttacks::write_ntag(NFCTag *tag)
{
    const size_t tag_size = tag->get_blocks_count();
    const size_t reserved_pages = tag_size == NTAG203_PAGES ? NTAG203_RESERVED_PAGES : NTAG21X_RESERVED_PAGES;
    uint8_t unwritable = 0;
    uint8_t uid[7];
    uint8_t uid_length;
    if(nfc_framework.get_tag_uid(uid, uid_length)) {
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
                unwritable++;
                LOG_ERROR("Error during writing block.\n");
            };
        }
    } else {
        Serial0.println("Unable to find card");
    }
    return unwritable;
}

uint8_t NFCAttacks::format_ntag(int pages)
{
    LOG_INFO("Formatting ntag...");
    uint8_t empty_tag_data[pages * NTAG_PAGE_SIZE] = {0};
    NFCTag empty_tag = NFCTag(empty_tag_data, 7, pages);
    return write_ntag(&empty_tag);
}

bool NFCAttacks::detect_felica(uint8_t *idm, uint8_t *pmm, uint16_t *sys_code) {
    return nfc_framework.felica_polling(idm, pmm, sys_code);
}

bool NFCAttacks::felica_read(uint8_t service_length, uint16_t *service_codes, uint8_t num_blocks, 
                            uint16_t *block_list, uint8_t data[][16]) {
    return nfc_framework.felica_read_without_encryption(service_length, service_codes, num_blocks, block_list, data);
}

bool NFCAttacks::felica_read(uint8_t num_blocks, uint16_t *block_list, uint8_t data[][16]) {
    uint16_t default_service_code[1] = { 0x000B };   // Default service code for reading. Should works for every card
    return nfc_framework.felica_read_without_encryption(1, default_service_code, num_blocks, block_list, data);
}


bool NFCAttacks::felica_write(uint8_t service_codes_list_length, uint16_t *service_codes, 
                            uint8_t block_number, uint16_t *block_list, uint8_t data[][16]) {

    return nfc_framework.felica_write_without_encryption(service_codes_list_length, service_codes,
                                                    block_number, block_list, data);
}

bool NFCAttacks::felica_write(uint8_t block_number, uint16_t *block_list, uint8_t data[][16]) {
    uint16_t default_service_code[1] = { 0x0009 };   // Default service code for writing. Should works for every card
    return nfc_framework.felica_write_without_encryption(1, default_service_code,block_number, block_list, data);
}

#define NFC_CONFIG_FILE "/nfc/config.json"
#define TAG_SIZE(length) length > 4 ? MIFARE_ULTRALIGHT_SIZE : MIFARE_CLASSIC_SIZE    // Ultralight have uid bit length and 512 bytes

NFCTag NFCAttacks::get_tag_towrite(uint8_t uid_length) {
    File nfc_config = open(NFC_CONFIG_FILE, "r");
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, nfc_config);
    uint8_t empty[1024];
    if (error) {
        LOG_ERROR("Invalid NFC configuration");
        return NFCTag(empty, 7);
    }
    // if uid_length == 7 search ntag
    File nfc_saved_tag = open(doc["ISO14443A"]["ntag_ultralight"]["tag_to_write"], "r");
    const size_t tag_size = TAG_SIZE(uid_length);
    byte buffer[tag_size] = { 0 };
    nfc_saved_tag.read(buffer, tag_size);
    return NFCTag(buffer, uid_length, NTAG213_PAGES);
}