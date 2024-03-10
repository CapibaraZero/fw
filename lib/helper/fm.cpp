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

#include "fm.hpp"

#include "posixsd.hpp"

vector<String> readlines(File file) {
  vector<String> lines = vector<String>();
  while (file.available()) {
    lines.push_back(file.readStringUntil('\n'));
  }
  return lines;
}

bool save_file(const char *path_name, uint8_t *payload) {
  File fptr = open(path_name, "w");  // Save to file
  if (fptr.write(payload, sizeof(payload)) > 0) {
    fptr.close();
    return true;
  } else
    return false;
}

void save_file(const char *path_name, uint8_t *payload, size_t sizeof_payload) {
  File fptr = open(path_name, "w");  // Save to file
  fptr.write(payload, sizeof_payload);
  fptr.close();
}
