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

duk_ret_t JSnow(duk_context *ctx) {
    duk_push_number(ctx, millis());
    return 1;
}

duk_ret_t JSdelay(duk_context *ctx) {
    if(duk_get_top(ctx) == 1)
        delay(duk_to_number(ctx, 0));
    return 0;
}

void init_js_timer(duk_context *ctx) {
    duk_push_c_function(ctx, JSnow, 0);
    duk_put_global_string(ctx, "now");
    duk_push_c_function(ctx, JSdelay, 1);
    duk_put_global_string(ctx, "delay");
}