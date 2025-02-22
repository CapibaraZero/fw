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
#include "../UI/navigation/NFC/NFCNavigation.hpp"
#include "ArduinoJson.h"
#include "flipper_zero_nfc_file_parser.hpp"
#include "navigation/navigation.hpp"
#include "nfc_attacks.hpp"
#include "nfc_tasks_types.h"
#include "posixsd.hpp"

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
  goto_nfc_polling_result_gui(
      uid, uid_length, NFCFramework::lookup_tag(atqa, sak, uid_length).name);
  free(pv);
  polling_in_progress = false;
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
  // LOG_INFO("Card found");
  params->gui->reset();
  init_nfc_felica_polling_result_gui(idm, pmm, sys_code);
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

void goto_home_nfc(NFCTasksParams *params) {
  // Go to home.
  // TODO: Port this in NFCNavigation
  // params->gui->reset();
  // params->gui->init_gui();
  // params->gui->set_current_position(0);
  // params->gui->set_selected_widget(0, true);
  nfc_cleanup();
  reset_uid();
  init_main_gui();
}

void dump_iso14443a_task(void *pv) {
  dump_in_progress = true;
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  DumpResult *result = (DumpResult *)malloc(sizeof(DumpResult));
  NFCTag tag = params->attacks->dump_tag(result);
  set_dumped_sectors(tag.get_blocks_count() - result->unreadable -
                     result->unauthenticated);
  set_unreadable_sectors(result->unreadable + result->unauthenticated);
  params->attacks->set_scanned_tag(&tag);
  delay(10000);
  goto_home_nfc(params);
  free(pv);
  dump_in_progress = false;
  vTaskDelete(NULL);
}

void dump_felica_task(void *pv) {
  dump_in_progress = true;
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  // DumpResult *result = (DumpResult *)malloc(sizeof(DumpResult));
  uint8_t unreadable = 0;
  NFCTag tag = params->attacks->felica_dump(14, &unreadable);
  LOG_INFO("Finished2");
  Serial.printf("Felica dump: %d\n", unreadable);
  set_dumped_sectors(14 - unreadable);
  set_unreadable_sectors(unreadable);
  params->attacks->set_scanned_tag(&tag);
  delay(10000);
  goto_home_nfc(params);
  free(pv);
  dump_in_progress = false;
  vTaskDelete(NULL);
}

void format_iso14443a_task(void *pv) {
  format_in_progress = true;
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  if(!exists("/NFC/keys.txt")) {
    params->gui->show_error_page("Missing keys file");
  } else {
    params->attacks->format_tag();
    delay(10000);
  }
  format_in_progress = false;
  // We don't need free(pv) here because we share same pointer between
  // bruteforce tasks
  vTaskDelete(NULL);
}

void format_update_ui_task(void *pv) {
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  while (params->attacks->get_bruteforce_status()) {
    set_formatted_sectors(params->attacks->get_tag_blocks(),
                          params->attacks->get_formatted_sectors());
    delay(1000);
  }
  delay(3000);
  goto_home_nfc(params);
  free(pv);
  vTaskDelete(NULL);
}

void format_felica_task(void *pv) {
  format_in_progress = true;
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  set_unformatted_sectors(14, params->attacks->felica_format(14));
  delay(10000);
  goto_home_nfc(params);
  free(pv);
  format_in_progress = false;
  vTaskDelete(NULL);
}

void bruteforce_iso14443a_task(void *pv) {
  bruteforce_in_progress = true;
  NFCTasksParams *params = static_cast<NFCTasksParams *>(pv);
  if(!exists("/NFC/keys.txt")) {
    params->gui->show_error_page("Missing keys file");
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
    nfc_bruteforce_set_tried_key(params->attacks->get_tried_keys());
    delay(1000);
  }
  delay(1000);
  nfc_bruteforce_set_tried_key(params->attacks->get_tried_keys());
  nfc_bruteforce_found_key();
  delay(2000);
  goto_home_nfc(params);
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
          set_wrote_sectors(++wrote_sectors);
        } else {
          set_unwritable_sectors(++unwritable_sectors);
        }
      }
    }
  } else {
    flipper_zero_nfc_parser(std::string(nfc_dump.readString().c_str()),
                            params->attacks);
  }
  delay(6000);
  goto_home_nfc(params);
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
        set_emv_type(known_aid[i].name);
        found = true;
      }
    }

    if(!found) {
      set_emv_type("Unknown");
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
      
      set_emv_pan(pan.c_str());
    } else {
      set_emv_pan("Unknown");
    }
    
    if(card.validfrom != nullptr) {
      std::string issuedate = BinToAscii(card.validfrom, 2);
      issuedate.insert(issuedate.begin() + 2, '/');
      set_emv_issue_date(issuedate.c_str());
    } else {
      set_emv_issue_date("Unknown");
    }

    if(card.validto != nullptr) {
      std::string validto = BinToAscii(card.validto, 2);
      validto.insert(validto.begin() + 2, '/');
      set_emv_expire_date(validto.c_str());
    }  else {
      set_emv_expire_date("Unknown");
    } 
  } else {
    set_emv_type("Can't parse EMV");
  }

  reading_emv = false;
  vTaskDelete(NULL);
}