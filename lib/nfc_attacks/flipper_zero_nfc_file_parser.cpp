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

#include <string>
#include <vector>

#include "../UI/navigation/NFC/NFCNavigation.hpp"
#include "nfc_attacks.hpp"

static int count_chars_in_line(const char *str, int pos) {
  int end_pos = pos;
  while (str[end_pos] != '\n') {
    end_pos++;
  }
  return end_pos;
}

static std::vector<std::string> split(std::string &s,
                                      const std::string &delimiter) {
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s);

  return tokens;
}

void flipper_zero_nfc_parser(std::string file, NFCAttacks *attacks) {
  int start_position = file.find("Device type:");
  start_position += std::string("Device type: ").size();
  int end_position = count_chars_in_line(file.c_str(), start_position);
  int type = 0;
  std::string nfc_type =
      file.substr(start_position, end_position - start_position);
  if (nfc_type == "Mifare Classic") {
    type = 0;
  } else if (nfc_type.find("NTAG") != std::string::npos) {
    type = 1;
  }
  start_position = type == 0 ? file.find("Block 0:") : file.find("Page 0:");
  std::string blocks_str = file.substr(start_position);
  size_t i = 0;
  std::vector<std::string> blocks = split(blocks_str, "\n");
  uint8_t key[6] = {0xFF, 0xFF, 0XFF, 0XFF, 0XFF, 0XFF};
  size_t wrote_sectors = 0;
  size_t unwritable_sectors = 0;
  for (std::string block : blocks) {
    if (block.find("Failed") == std::string::npos && block != "") {
      uint8_t data[type == 0 ? 16 : 4];
      size_t substr_space = i < 10 ? 9 : 10;
      if (type != 0) {
        substr_space--;
      }
      std::string parsed_blocks = block.substr(substr_space);
      std::vector<std::string> values = split(parsed_blocks, " ");
      size_t j = 0;
      for (std::string val : values) {
        data[j++] = val != "??" ? strtol(val.c_str(), NULL, 16) : 0xFF;
      }
      bool success = false;
      if (type == 0) {
        success = attacks->write_sector(i++, data, 0, key);
      } else {
        success = attacks->write_ntag(i++, data);
      }
      if (success) {
        set_wrote_sectors(++wrote_sectors);
      } else {
        set_unwritable_sectors(++unwritable_sectors);
      }
    }
  }
}