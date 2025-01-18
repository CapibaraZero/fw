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

#include "Arduino.h"
#include "duktape.h"
#include "nfc_attacks.hpp"

#include "ArduinoJson.h"

extern NFCAttacks nfc_attacks;
//static NFCTag dumped_tag;

/// @brief Read UID from ISO14443a NFC tag
/// @param ctx Duktape context
/// @return 4-7 array length for UID
duk_ret_t nfc_read_uid_iso14443a(duk_context *ctx) {
    uint8_t uid[7];
    uint8_t uid_len = 0;
    nfc_attacks.read_uid(uid, &uid_len);
    duk_idx_t array_idx = duk_push_array(ctx);
    for (size_t i = 0; i < uid_len; i++) {
        duk_push_uint(ctx, uid[i]);
        duk_put_prop_index(ctx, array_idx, i);
    }
    return 1;
}

void init_js_nfc(duk_context *ctx) {
    duk_push_c_function(ctx, nfc_read_uid_iso14443a, 0);
    duk_put_global_string(ctx, "nfc_read_uid_iso14443a");
}