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

#include "../../include/debug.h"
#include "ArduinoJson.h"
#include "flipper_zero_nfc_file_parser.hpp"
#include "navigation/navigation.hpp"
#include "nfc_attacks.hpp"
#include "nfc_tasks_types.h"
#include "posixsd.hpp"
#include <lvgl.h>
#include "screens.h"
#include "vars.h"
#include "hex2str.hpp"
#include "ui.h"

bool polling_in_progress = false;
bool dump_in_progress = false;
bool format_in_progress = false;
bool bruteforce_in_progress = false;

uint8_t uid[8];
static uint8_t uid_length = 0;

uint8_t idm[8] = {0};
uint8_t pmm[8] = {0};
uint16_t sys_code = 0;

void reset_uid(void) {
  memset(uid, 0, 8);
  uid_length = 0;
}

void reset_felica(void) {
  memset(idm, 0, 8);
  memset(pmm, 0, 8);
  sys_code = 0;
}

void mifare_polling_task(void *pv) {
  polling_in_progress = true;
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  LOG_INFO("Start polling task");
  uint16_t atqa = 0;
  uint8_t sak = 0;
  while (uid_length == 0) {
    params->attacks->read_uid(uid, &uid_length, &atqa, &sak);
    delay(500);
  }
  LOG_INFO("Card found\n");
  Serial.print("ATQA: ");
  Serial.println(atqa, HEX);
  Serial.print("SAK: ");
  Serial.println(sak, HEX);

  create_screen_nfciso14443_ainfo();
  loadScreen(SCREEN_ID_NFCISO14443_AINFO);

  set_var_nfc_tag_type(NFCFramework::lookup_tag(atqa, sak, uid_length).name);
  set_var_nfc_atqa(("ATQA: " + String(atqa, HEX)).c_str());
  set_var_nfc_sak(("SAK: " + String(sak, HEX)).c_str());

  free(pv);
  polling_in_progress = false;
  uid_length = 0; // Reset for next usage
  vTaskDelete(NULL);
}

void felica_polling_task(void *pv) {
  polling_in_progress = true;
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  LOG_INFO("Start polling task");
  while (sys_code == 0) {
    params->attacks->detect_felica(idm, pmm, &sys_code);
    delay(500);
  }


  LOG_INFO("Sys code: ");
#ifdef ARDUINO_NANO_ESP32
  Serial.println(sys_code, HEX);
#else
  Serial0.println(sys_code, HEX);
#endif

  create_screen_nfciso18092_ainfo();
  loadScreen(SCREEN_ID_NFCISO18092_AINFO);

  set_var_nfc_tag_type("FeliCa found!");
  set_var_nfc_atqa(("IDm: " + hextostr(idm, 8)).c_str());
  set_var_nfc_sak(("PMm: " + hextostr(pmm, 8)).c_str());
  set_var_nfc_sys_code(("Sys. Code: "+ String(sys_code, HEX)).c_str());
  
  free(pv);
  polling_in_progress = false;

  vTaskDelete(NULL);
}

void get_uid(uint8_t *_uid, uint8_t *_uid_length) {
  memcpy(_uid, uid, uid_length);
  *_uid_length = uid_length;
}

void get_card_info(uint8_t *_idm, uint8_t *_pmm, uint16_t *_sys_code) {
  _idm = idm;
  _pmm = pmm;
  *_sys_code = sys_code;
}

void goto_home_nfc() {
  create_screen_nfc_page();
  loadScreen(SCREEN_ID_NFC_PAGE);
}

void dump_felica_task(void *pv) {
  dump_in_progress = true;
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  uint8_t unreadable = 0;
  NFCTag tag = params->attacks->felica_dump(14, &unreadable);
  LOG_INFO("Finished2");
  Serial.printf("Felica dump: %d\n", unreadable);
  set_var_nfc_felica_read_sector(("Read sectors: " + String(14 - unreadable)).c_str());
  set_var_nfc_felica_unreadable_sectors(("Unreadable sectors: " + String(unreadable)).c_str());
  params->attacks->set_scanned_tag(&tag);
  delay(5000);
  goto_home_nfc();
  free(pv);
  dump_in_progress = false;
  vTaskDelete(NULL);
}

void format_iso14443a_task(void *pv) {
  format_in_progress = true;
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  if(!exists("/NFC/keys.txt")) {
    Serial.println("Missing keys file");
    params->attacks->set_bruteforce_status(false);
    // params->gui->show_error_page("Missing keys file");
  } else {
    params->attacks->format_tag();
    delay(10000);
  }
  format_in_progress = false;

  if(!exists("/NFC/keys.txt")) {
    set_var_nfc_written_sectors("Missing keys file");  // Show a message error for user
    set_var_nfc_unwritable_sectors("");
  }
  // We don't need free(pv) here because we share same pointer between
  // bruteforce tasks
  vTaskDelete(NULL);
}

void format_update_ui_task(void *pv) {
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  while (params->attacks->get_bruteforce_status()) {
    set_var_nfc_written_sectors(("Formatted: " + String(params->attacks->get_formatted_sectors())).c_str());
    set_var_nfc_unwritable_sectors(("Unwritable: " + String(params->attacks->get_tag_blocks())).c_str());
    delay(1000);
  }
  delay(3000);
  goto_home_nfc();
  free(pv);
  vTaskDelete(NULL);
}

void bruteforce_iso14443a_task(void *pv) {
  bruteforce_in_progress = true;
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  if(!exists("/NFC/keys.txt")) {
    set_var_nfc_found_keys("Missing keys file");
    params->attacks->set_bruteforce_status(false);
  } else {
    params->attacks->bruteforce();
  }
  bruteforce_in_progress = false;
  // We don't need free(pv) here because we share same pointer between
  // bruteforce tasks
  vTaskDelete(NULL);
}

void bruteforce_update_ui_task(void *pv) {
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  while (params->attacks->get_bruteforce_status()) {
    set_var_nfc_tried_keys(("Tried keys: " + String(params->attacks->get_tried_keys())).c_str());
    delay(1000);
  }
  delay(1000);
  set_var_nfc_tried_keys(("Tried keys: " + String(params->attacks->get_tried_keys())).c_str());
  // nfc_bruteforce_set_tried_key(params->attacks->get_tried_keys());
  // nfc_bruteforce_found_key();
  set_var_nfc_found_keys("Saving results...");
  delay(2000);
  goto_home_nfc();
  free(pv);
  vTaskDelete(NULL);
}

void write_nfc_sectors(void *pv) {
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  JsonDocument doc;
  File nfc_dump = open("/NFC/dumps/" + (String)params->path, "r");
  if (strstr(params->path, ".json") != NULL) {
    DeserializationError error = deserializeJson(doc, nfc_dump);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
    } else {
      const char *type = doc["type"];  // Type of tag
      size_t wrote_sectors = 0;
      size_t unwritable_sectors = 0;
      for (JsonPair block : doc["blocks"].as<JsonObject>()) {
        int block_key = atoi(block.key().c_str());

        int block_value_key_type = block.value()["key_type"];

        uint8_t key[6];
        size_t i = 0;

        for (uint8_t key_byte : block.value()["key"].as<JsonArray>()) {
          key[i++] = key_byte;
        }

        uint8_t data[type == "0" ? 16 : 4];
        i = 0;
        for (uint8_t data_byte : block.value()["data"].as<JsonArray>()) {
          data[i++] = data_byte;
        }

        bool success = false;
        if (type == "0") {
          success = params->attacks->write_sector(i++, data, 0, key);
        } else {
          success = params->attacks->write_ntag(i++, data);
        }
        if (success) {
          set_var_nfc_written_sectors(("Written sectors: " + String(++wrote_sectors)).c_str());
        } else {
          set_var_nfc_unwritable_sectors(("Unwritable sectors: " + String(++unwritable_sectors)).c_str());
        }
      }
    }
  } else {
    flipper_zero_nfc_parser(std::string(nfc_dump.readString().c_str()),
                            params->attacks);
  }
  delay(6000);
  goto_home_nfc();
  free(pv);
  vTaskDelete(NULL);
}

void emulate_iso14443anfc(void *pv) {
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  while (true) {
    params->attacks->emulate_tag(params->uid);
  }
}

void emulate_iso18092nfc(void *pv) {
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  while (true) {
    params->attacks->emulate_tag(params->idm, params->pmm, params->sys_code);
  }
}

// From https://github.com/huckor/BER-TLV
std::string BinToAscii(uint8_t *BinData, size_t size)
{
	char AsciiHexNo[5];
	std::string Return;

	for(int i = 0; i < size; i++)
	{
		sprintf(AsciiHexNo, "%02X", BinData[i]);
		Return += AsciiHexNo;
	}

	return Return;
}

typedef struct EMVAID {
  uint8_t aid[7];
  const char *name;
} EMVAID;

#define AID_DICT_SIZE 11
// http://hartleyenterprises.com/listAID.html
const EMVAID known_aid[AID_DICT_SIZE] = {
  // MasterCard
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x04, 0x10, 0x10},
    .name = "MasterCard"
  },
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x04, 0x22, 0x03},
    .name = "U.S Maestro"
  },
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x04, 0x30, 0x60},
    .name = "Maestro"
  },
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x04, 0x60, 0x00},
    .name = "Cirrus"
  },
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x04, 0x99, 0x99},
    .name = "MasterCard"
  },
  // Visa
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10},
    .name = "Visa"
  },
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x03, 0x20, 0x10},
    .name = "Electron"
  },
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x03, 0x20, 0x20},
    .name = "V-Pay"
  },
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x03, 0x30, 0x10},
    .name = "Visa"
  },
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x03, 0x80, 0x10},
    .name = "Visa"
  },
  {
    .aid = {0xA0, 0x00, 0x00, 0x00, 0x98, 0x08, 0x40},
    .name = "Visa"
  }
};

extern bool reading_emv;

void read_emv_card_task(void *pv) {
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  EMVCard card = params->attacks->read_emv_card();

  if(card.parsed) {
    bool found = false;
    for (size_t i = 0; i < AID_DICT_SIZE && !found; i++) {
      if(memcmp(card.aid, known_aid[i].aid, 7) == 0) {
        set_var_nfc_emv_type(known_aid[i].name);
        found = true;
      }
    }

    if(!found) {
      set_var_nfc_emv_type("Unknown");
    }

    if(card.pan != nullptr) {
      std::string pan = BinToAscii(card.pan, card.pan_len);

      /* Add some spacing */
      size_t pad = 0;
      for (size_t i = 0; i < pan.size(); i++) {
        if(i % 4 == 0 && i != 0) {
          pan.insert(pan.begin() + i + (pad++), ' ');
        }
      }

      set_var_nfc_emv_card_number(pan.c_str());
    } else {
      set_var_nfc_emv_card_number("Unknown");
    }

    if(card.validfrom != nullptr) {
      std::string issuedate = BinToAscii(card.validfrom, 2);
      issuedate.insert(issuedate.begin() + 2, '/');
      set_var_nfc_emv_card_issue(issuedate.c_str());
    } else {
      set_var_nfc_emv_card_issue("Unknown");
    }

    if(card.validto != nullptr) {
      std::string validto = BinToAscii(card.validto, 2);
      validto.insert(validto.begin() + 2, '/');
      set_var_nfc_emv_card_expire(validto.c_str());
    }  else {
      set_var_nfc_emv_card_expire("Unknown");
    }
  } else {
    set_var_nfc_emv_type("Can't parse EMV");
  }

  reading_emv = false;
  vTaskDelete(NULL);
}
