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
#include "IrFramework.hpp"
//#include "IRremote.hpp"
#include "../../include/pins.h"
#include "navigation/IR/IRNavigation.hpp"
#include "ArduinoJson.h"

static IrFramework *irframework;

duk_ret_t init_ir(duk_context *ctx) {
    irframework = new IrFramework(IR_RECEIVER_PIN, IR_EMITTER_PIN);
    return 0;
}

duk_ret_t read_ir(duk_context *ctx) {
    duk_push_boolean(ctx, irframework->read_signal());
    return 1;
}

duk_ret_t ir_signal_to_str(duk_context *ctx) {
    RecordedSignal signal = irframework->get_decoded_signal();
    JsonDocument doc;
    doc["protocol"] = signal.protocol;
    doc["address"] = signal.address;
    doc["command"] = signal.command;
    doc["number_of_bits"] = signal.numberOfBits;
    doc["extra"] = signal.extra;
    doc["decoded_raw_data"] = signal.decodedRawData;
    doc["raw_len"] = signal.raw_len;
    doc["flags"] = signal.flags;
    JsonArray raw_data = doc["raw_data"].to<JsonArray>();
    for (size_t i = 0; i < signal.raw_len; i++) {
        raw_data.add(signal.decodedRawDataArray[i]);
    }
    doc.shrinkToFit();
    String res;
    serializeJson(doc, res);
    duk_push_string(ctx, res.c_str());
    return 1;
}

duk_ret_t send_ir_protocol(duk_context *ctx) {
    if(duk_is_number(ctx, 0) && duk_is_number(ctx, 1) && duk_is_number(ctx, 2)) {
       int protocol = duk_to_int(ctx, 0);
       uint16_t addr = duk_to_uint(ctx, 1);
       uint16_t cmd = duk_to_uint(ctx, 2);
       uint16_t num_of_bits = 0;
       if(duk_get_top(ctx) == 4 && duk_is_number(ctx, 3)) {
        num_of_bits = duk_get_uint(ctx, 3);
       }
       RecordedSignal signal = {
        .protocol = protocol,
        .address = addr,
        .command = cmd,
        .numberOfBits = num_of_bits
       };
       irframework->send_protocol_signal(signal);
    }
    return 0;
}

void init_js_ir(duk_context *ctx) {
    duk_push_c_function(ctx, init_ir, 0);
    duk_put_global_string(ctx, "init_ir");
    duk_push_c_function(ctx, read_ir, 0);
    duk_put_global_string(ctx, "read_ir_signal");
    duk_push_c_function(ctx, ir_signal_to_str, 0);
    duk_put_global_string(ctx, "ir_signal_to_str");
    duk_push_c_function(ctx, send_ir_protocol, 4);
    duk_put_global_string(ctx, "send_ir_signal");
}