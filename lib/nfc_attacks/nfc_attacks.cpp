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

#include "nfc_attacks.hpp"

#include <algorithm>
#include <list>
#include <vector>

#include "../../include/debug.h"
#include "ArduinoJson.h"
#include "fm.hpp"
#include "helper.hpp"
#include "posixsd.hpp"

using namespace std;

#define NFC_KEYS_FILE "/NFC/keys.txt"

NFCAttacks::NFCAttacks() {
  if (!nfc_framework.ready()) {
    LOG_ERROR("PN532 not found, trying to restart\n");
    ESP.restart();
  } else {
    LOG_SUCCESS("PN532 found!\n");
  }
}
bool NFCAttacks::is_there_null_blocks(NFCTag *tag) {
  for (size_t i = 0; i < tag->get_blocks_count(); i++) {
    uint8_t block[BLOCK_SIZE] = {0};
    tag->get_block(i, block);
    for (size_t j = 0; j < 16; j++) {
      if (block[j] == -1) {
        return true;
      }
    }
  }
  return false;
}

static void c_array_to_jsonarray(uint8_t *arr, JsonArray *json_array, size_t len) {
  for (size_t i = 0; i < len; i++)
  {
    json_array->add(arr[i]);
  }
}

void bruteforce_res_to_sd(std::map<uint8_t, SectorResult> *bruteforce_result) {
  StaticJsonDocument<6200> bruteforce_result_json;
  Serial.println("Saving to SD");
  JsonArray uid = bruteforce_result_json.createNestedArray("uid");
  c_array_to_jsonarray(bruteforce_result->at(0).uid, &uid, bruteforce_result->at(0).uid_len);
  JsonArray result = bruteforce_result_json.createNestedArray("result");
  for (auto sector_res_raw : *bruteforce_result) {
    JsonObject sector_res_json = result.createNestedObject();
    SectorResult sector_res = sector_res_raw.second;
    sector_res_json["id"] = sector_res_raw.first;
    sector_res_json["key_a_found"] = sector_res.key_a_found;
    sector_res_json["key_b_found"] = sector_res.key_b_found;
    JsonArray key_a = sector_res_json.createNestedArray("key_a");
    c_array_to_jsonarray(sector_res.key_a, &key_a, 6);
    JsonArray key_b = sector_res_json.createNestedArray("key_b");
    c_array_to_jsonarray(sector_res.key_b, &key_b, 6);
    Serial.println(uxTaskGetStackHighWaterMark(NULL));
  }
  String final_res = "";
  serializeJsonPretty(bruteforce_result_json, final_res);
  // Name: result_uid.json UID is got at index 0 because we save only in sector 0
  File res = open("/NFC/result_" + String(millis()) + ".json", "w");
  Serial.println(uxTaskGetStackHighWaterMark(NULL));
  if(res.available()) {
    res.print(final_res);
    res.close();
  }
  Serial.println(uxTaskGetStackHighWaterMark(NULL));
}

static void parse_str_to_arr(String *str, uint8_t *out, size_t len) {
  for (size_t i = 0; i < 6; i++) {
    out[i] = strtol(str->substring(0,2).c_str(), NULL, 16);
    if(str->length() != 2)
      str->remove(0, 2);
  }
}

void NFCAttacks::auth_sector(uint8_t sector, uint8_t *key, KeyType key_type, uint8_t *out_key, bool *key_found) {
  *key_found = nfc_framework.auth_tag(key, sector, key_type);
  if(*key_found)
    memcpy(out_key, key, 6);
}

bool NFCAttacks::bruteforce() {
  bruteforce_status = true;
  File keys = open(NFC_KEYS_FILE, "r");
  std::map<uint8_t, SectorResult> bruteforce_result;
  // List of trailer of sector 0..63
  list<uint8_t> know_sector = {
    0,  // Sector 0
    4,  // Sector 1
    8,  // Sector 2
    12, // Sector 3
    16, // Sector 4
    20, // Sector 5
    24, // Sector 6
    28, // Sector 7
    32, // Sector 8
    36, // Sector 9
    40, // Sector 10
    44, // Sector 11
    48, // Sector 12
    52, // Sector 13
    56, // Sector 14
    60  // Sector 15
  };
  uint16_t atqa = 0;
  uint8_t sak = 0;
  nfc_framework.get_tag_uid(bruteforce_result[0].uid, &bruteforce_result[0].uid_len, &atqa, &sak);
  TagType tag = NFCFramework::lookup_tag(atqa, sak, bruteforce_result[0].uid_len);
  if(tag.blocks == 20) {
    know_sector.resize(5);
  }
  if (keys.available()) {
    LOG_INFO("File found!\n");
    vector<String> lines = readlines(keys);  // Read all lines
    for (String line : lines) {
      if (line[0] == '#')  // If is a comment, skip
        continue; 
      vector<String> raw_key = string_split(
          (char *)line.c_str(), " ");  // String string for each space
      uint8_t parsed_key[6];
      for (String key_byte : raw_key) {
        SERIAL_DEVICE.printf("%s\n", key_byte.c_str());
        parse_str_to_arr(&key_byte, parsed_key, 6);
      }
      for (uint8_t sector : know_sector)
      {
        if(bruteforce_result.find(sector) == bruteforce_result.end()){
          bruteforce_result.insert({sector, SectorResult()});
        }
        if(!bruteforce_result[sector].key_a_found){
          auth_sector(sector, parsed_key, KEY_A, bruteforce_result[sector].key_a, &bruteforce_result[sector].key_a_found);
        }
        if(!bruteforce_result[sector].key_b_found){
          auth_sector(sector, parsed_key, KEY_B, bruteforce_result[sector].key_b, &bruteforce_result[sector].key_b_found);
          Serial.println(uxTaskGetStackHighWaterMark(NULL));
        }
        if(bruteforce_result[sector].key_a_found && bruteforce_result[sector].key_b_found) {
            know_sector.remove(sector); 
        }
        Serial.println(uxTaskGetStackHighWaterMark(NULL));
      }
      if(know_sector.size() == 0){
        bruteforce_status = false;
        bruteforce_res_to_sd(&bruteforce_result);
        return true;
      }
      tried_keys++;  // For statistics use
    }
  } else {
    LOG_ERROR("Keys file not found.\n");
  }
  bruteforce_res_to_sd(&bruteforce_result);
  bruteforce_status = false;
  return false;
}

void NFCAttacks::read_uid(uint8_t *uid, uint8_t *uid_length) {
  LOG_INFO("Read UID: ");
  if (!nfc_framework.get_tag_uid(uid, uid_length)) {
    uid = NULL;
    uid_length = NULL;
  };
}

void NFCAttacks::read_uid(uint8_t *uid, uint8_t *uid_length, uint16_t *atqa, uint8_t *sak) {
  LOG_INFO("Read UID: ");
  if (!nfc_framework.get_tag_uid(uid, uid_length, atqa, sak)) {
    uid = NULL;
    uid_length = NULL;
  };
}

NFCTag NFCAttacks::dump_tag(DumpResult *result) {
  uint8_t key_universal[6] = {0xFF, 0xFF, 0xFF,
                              0xFF, 0xFF, 0xFF};  // Universal key
  size_t key_length;
  uint8_t *data = nfc_framework.dump_tag(key_universal, &key_length, result);
  if (key_length == 4)
    return NFCTag(data, key_length);  // uint8_t to NFCTag object
  else
    return NFCTag(data, key_length, NTAG213_PAGES);  // uint8_t to NFCTag object
}

NFCTag NFCAttacks::dump_tag(uint8_t *key, DumpResult *result) {
  size_t key_length;
  return NFCTag(nfc_framework.dump_tag(key, &key_length, result),
                key_length);  // uint8_t to NFCTag object
}

NFCTag NFCAttacks::dump_ntag(int pages) {
  return NFCTag(nfc_framework.dump_ntag2xx_tag(pages), 7, pages);
}

uint8_t NFCAttacks::write_tag(NFCTag *tag) {
  uint8_t key_universal[6] = {0xFF, 0xFF, 0xFF,
                              0xFF, 0xFF, 0xFF};  // Universal key
  uint8_t unwritable = 0;
  uint8_t uid[7];
  uint8_t uid_length;
  if (nfc_framework.get_tag_uid(uid, uid_length)) {
    for (size_t i = 0; i < tag->get_blocks_count(); i++) {
      Serial.printf("Writing block: %i\n", i);
      uint8_t block[BLOCK_SIZE] = {0};
      tag->get_block(i, block);
      if (nfc_framework.write_tag(i, block, key_universal)) {
        LOG_SUCCESS("Block written correctly\n");
      } else {
        unwritable++;
        LOG_ERROR("Error during writing block.");
      };
    }
  } else {
    LOG_INFO("Unable to find card");
  }
  return unwritable;
}

uint8_t NFCAttacks::write_tag(NFCTag *tag, int starting_block) {
  uint8_t key_universal[6] = {0xFF, 0xFF, 0xFF,
                              0xFF, 0xFF, 0xFF};  // Universal key
  uint8_t unwritable = 0;
  uint8_t uid[7];
  uint8_t uid_length;
  // Avoid crashing if no card is present
  if (nfc_framework.get_tag_uid(uid, uid_length)) {
    for (size_t i = starting_block; i < tag->get_blocks_count(); i++) {
      Serial.printf("Writing block: %i\n", i);
      uint8_t block[BLOCK_SIZE] = {0};
      tag->get_block(i, block);
      if (nfc_framework.write_tag(i, block, key_universal)) {
        LOG_SUCCESS("Block written correctly\n");
      } else {
        unwritable++;
        LOG_ERROR("Error during writing block.");
      };
    }
  } else {
    LOG_INFO("Unable to find card");
  }
  return unwritable;
}

void NFCAttacks::write_tag(NFCTag *tag, uint8_t *key) {
  for (size_t i = 0; i < tag->get_blocks_count(); i++) {
    Serial.printf("Writing block: %i\n", i);
    uint8_t block[BLOCK_SIZE] = {0};
    tag->get_block(i, block);
    if (nfc_framework.write_tag(i, block, key)) {
      LOG_SUCCESS("Block written correctly\n");
    } else {
      LOG_ERROR("Error during writing block.");
    };
  }
}

void NFCAttacks::write_tag(NFCTag *tag, uint8_t *key, int starting_block) {
  for (size_t i = starting_block; i < tag->get_blocks_count(); i++) {
    Serial.printf("Writing block: %i\n", i);
    uint8_t block[BLOCK_SIZE] = {0};
    tag->get_block(i, block);
    if (nfc_framework.write_tag(i, block, key)) {
      LOG_SUCCESS("Block written correctly\n");
    } else {
      LOG_ERROR("Error during writing block.");
    };
  }
}

uint8_t NFCAttacks::format_tag(bool ultralight) {
  LOG_INFO("Formatting tag...");
  uint8_t empty_tag_data[ultralight ? MIFARE_ULTRALIGHT_SIZE
                                    : MIFARE_CLASSIC_SIZE] = {0};
  NFCTag empty_tag = NFCTag(
      empty_tag_data, 4);  // Uid lenght is dummy here since it's an empty key
  return write_tag(&empty_tag, ultralight ? 7 : 4);
}

void NFCAttacks::format_tag(uint8_t *key, bool ultralight) {
  LOG_INFO("Formatting tag...");
  uint8_t empty_tag_data[ultralight ? MIFARE_ULTRALIGHT_SIZE
                                    : MIFARE_CLASSIC_SIZE] = {0};
  NFCTag empty_tag = NFCTag(
      empty_tag_data, 4);  // Uid lenght is dummy here since it's an empty key
  write_tag(&empty_tag, key, ultralight ? 7 : 4);
}

uint8_t NFCAttacks::write_ntag(NFCTag *tag) {
  const size_t tag_size = tag->get_blocks_count();
  const size_t reserved_pages = tag_size == NTAG203_PAGES
                                    ? NTAG203_RESERVED_PAGES
                                    : NTAG21X_RESERVED_PAGES;
  uint8_t unwritable = 0;
  uint8_t uid[7];
  uint8_t uid_length;
  if (nfc_framework.get_tag_uid(uid, uid_length)) {
    /* Skip non-user sectors since it's not writable */
    for (size_t i = 4; i != tag_size - reserved_pages; i++) {
      Serial.printf("Writing block: %i\n", i);
      uint8_t block[4];
      tag->get_block(i, block);
      if (nfc_framework.write_ntag2xx_page(i, block)) {
        LOG_SUCCESS("Block written correctly\n");
      } else {
        unwritable++;
        LOG_ERROR("Error during writing block.\n");
      };
    }
  } else {
    LOG_INFO("Unable to find card");
  }
  return unwritable;
}

uint8_t NFCAttacks::format_ntag(int pages) {
  LOG_INFO("Formatting ntag...");
  uint8_t empty_tag_data[pages * NTAG_PAGE_SIZE] = {0};
  NFCTag empty_tag = NFCTag(empty_tag_data, 7, pages);
  return write_ntag(&empty_tag);
}

bool NFCAttacks::detect_felica(uint8_t *idm, uint8_t *pmm, uint16_t *sys_code) {
  return nfc_framework.felica_polling(idm, pmm, sys_code);
}

bool NFCAttacks::felica_read(uint8_t service_length, uint16_t *service_codes,
                             uint8_t num_blocks, uint16_t *block_list,
                             uint8_t data[][16]) {
  return nfc_framework.felica_read_without_encryption(
      service_length, service_codes, num_blocks, block_list, data);
}

int NFCAttacks::felica_read(uint8_t num_blocks, uint16_t *block_list,
                            uint8_t data[][16]) {
  uint16_t default_service_code[1] = {
      0x000B};  // Default service code for reading. Should works for every card
  return nfc_framework.felica_read_without_encryption(
      1, default_service_code, num_blocks, block_list, data);
}

bool NFCAttacks::felica_write(uint8_t service_codes_list_length,
                              uint16_t *service_codes, uint8_t block_number,
                              uint16_t *block_list, uint8_t data[][16]) {
  return nfc_framework.felica_write_without_encryption(
      service_codes_list_length, service_codes, block_number, block_list, data);
}

int NFCAttacks::felica_write(uint8_t block_number, uint16_t *block_list,
                             uint8_t data[][16]) {
  uint16_t default_service_code[1] = {
      0x0009};  // Default service code for writing. Should works for every card
  return nfc_framework.felica_write_without_encryption(
      1, default_service_code, block_number, block_list, data);
}

int NFCAttacks::felica_write(NFCTag *tag) {
  uint8_t blocks[14][16] = {0};
  tag->get_felica_data(blocks);
  for (uint16_t i = 0x8000; i < 0x8000 + 16; i++) {
    uint16_t block_list[1] = {i};
    felica_write(i, block_list, &blocks[i]);
  }
  return 0;
}

uint8_t NFCAttacks::felica_format(uint8_t blocks) {
  uint8_t unformattable = 0;
  for (uint16_t i = 0x8000; i < 0x8000 + blocks; i++) {
    uint16_t block_list[1] = {i};
    uint8_t block_data[1][16] = {0};
    int res = felica_write(1, block_list, block_data);
    Serial.printf("Write result: %d\n", res);
    if (res != 1) {
      unformattable++;
    }
  }
  return unformattable;
}

NFCTag NFCAttacks::felica_dump(int blocks, uint8_t *unreadable) {
  uint8_t data[14][16];
  uint8_t _idm[8];
  uint8_t _pmm[8];
  uint16_t _sys_code;
  if (detect_felica(_idm, _pmm, &_sys_code)) {
    for (uint16_t i = 0x8000; i < 0x8000 + blocks; i++) {
      uint16_t block_list[1] = {i};
      uint8_t block_data[1][16] = {0};
      int res = felica_read(1, block_list, block_data);
      Serial.printf("Write result: %d\n", res);
      if (res != 1) {
        *unreadable++;
        memset(&data[i][0], 0, 16);
      } else {
        memcpy(&data[i][0], &block_data[0][0], 16);
      }
    }
  } else {
    uint8_t empty[14][16] = {0};
    return NFCTag(_idm, _pmm, _sys_code, empty);
  }
  LOG_INFO("FInished");
  return NFCTag(_idm, _pmm, _sys_code, data);
}

uint8_t NFCAttacks::felica_dump(int blocks, uint8_t data[][16]) {
  uint8_t unreadable = 0;
  for (uint16_t i = 0x8000; i < 0x8000 + blocks; i++) {
    uint16_t block_list[1] = {i};
    uint8_t block_data[1][16] = {0};
    int res = felica_read(1, block_list, block_data);
    Serial.printf("Write result: %d\n", res);
    if (res != 1) {
      unreadable++;
      memset(&data[i][0], 0, 16);
    } else {
      memcpy(&data[i][0], &block_data[0][0], 16);
    }
  }
  return unreadable;
}

bool NFCAttacks::felica_clone(NFCTag *tag) {
  uint8_t data[14][16] = {0};
  tag->get_felica_data(data);
  bool status = true;
  for (uint16_t i = 0; i < 14; i++) {
    uint16_t block_list[1] = {i};
    int res = felica_write(i, block_list, &data[i]);
    Serial.printf("Write result: %d\n", res);
    status = res == 1 && status;
  }

  return status;
}

#define NFC_CONFIG_FILE "/nfc/config.json"
#define TAG_SIZE(length)       \
  length > 4                   \
      ? MIFARE_ULTRALIGHT_SIZE \
      : MIFARE_CLASSIC_SIZE  // Ultralight have uid bit length and 512 bytes

NFCTag NFCAttacks::get_tag_towrite(uint8_t uid_length) {
  File nfc_config = open(NFC_CONFIG_FILE, "r");
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, nfc_config);
  if (error) {
    uint8_t empty[1024];
    LOG_ERROR("Invalid NFC configuration");
    return NFCTag(empty, 7);
  }
  // if uid_length == 7 search ntag
  File nfc_saved_tag =
      open(doc["ISO14443A"]["ntag_ultralight"]["tag_to_write"], "r");
  if (!nfc_saved_tag.available()) {
    uint8_t empty[1024];
    LOG_ERROR("Invalid NFC dump");
    return NFCTag(empty, 7);
  }
  const size_t tag_size = TAG_SIZE(uid_length);
  byte buffer[tag_size] = {0};
  nfc_saved_tag.read(buffer, tag_size);
  return NFCTag(buffer, uid_length, NTAG213_PAGES);
}

NFCTag NFCAttacks::get_felica_towrite() {
  File nfc_config = open(NFC_CONFIG_FILE, "r");
  uint8_t idm[8] = {0};
  uint8_t pmm[8] = {0};
  uint16_t sys_code = 0;
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, nfc_config);
  if (error) {
    uint8_t empty[1024];
    LOG_ERROR("Invalid NFC configuration");
    return NFCTag(empty, 7);
  }
  File nfc_saved_tag = open(doc["ISO18092"]["tag_to_write"], "r");
  if (!nfc_saved_tag.available()) {
    uint8_t empty[1024];
    LOG_ERROR("Invalid NFC dump");
    return NFCTag(empty, 7);
  }
  byte buffer[14 * 16] = {0};
  nfc_saved_tag.read(buffer, 14 * 16);
  uint8_t data[14][16] = {0};
  for (uint8_t i = 0; i < 14; i++) {
    memcpy(&data[i][0], &buffer[i * 16], 16);
  }
  return NFCTag(idm, pmm, sys_code, data);
}