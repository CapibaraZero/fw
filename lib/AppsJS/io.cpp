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
#include "../../include/debug.h"

duk_ret_t JSpinMode(duk_context *ctx) {
    if(duk_get_top(ctx) == 2)
        pinMode(duk_to_number(ctx, 0), duk_to_number(ctx, 1));
    return 0;
}

duk_ret_t JSdigitalRead(duk_context *ctx) {
    if(duk_get_top(ctx) == 1)
        duk_push_number(ctx, digitalRead(duk_to_number(ctx, 0)));
    return 1;
}

duk_ret_t JSdigitalWrite(duk_context *ctx) {
    if(duk_get_top(ctx) == 2)
        digitalWrite(duk_to_number(ctx, 0), duk_to_number(ctx, 1));
    return 0;
}

duk_ret_t js_print(duk_context *ctx) {
    if(duk_is_string(ctx, 0))
        SERIAL_DEVICE.printf(duk_to_string(ctx,0));
    return 0;
}

void init_js_io(duk_context *ctx) {
    duk_push_c_function(ctx, JSpinMode, 2);
    duk_put_global_string(ctx, "pinMode");
    duk_push_c_function(ctx, JSdigitalRead, 1);
    duk_put_global_string(ctx, "digitalRead");
    duk_push_c_function(ctx, JSdigitalWrite, 2);
    duk_put_global_string(ctx, "digitalWrite");
    duk_push_c_function(ctx, js_print, 1);
    duk_put_global_string(ctx, "print");
}