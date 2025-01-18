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
#include "posixsd.hpp"
#include "fm.hpp"

duk_ret_t write_to_sd(duk_context *ctx) {
    if(duk_is_string(ctx, 0) && duk_is_string(ctx, 1)) {
        File file = open(duk_get_string(ctx, 0), "w");
        if(file) {
            if(file.print(duk_get_string(ctx, 1)) != 0) {
                duk_push_true(ctx);
            } else {
                duk_push_false(ctx);
            }
            file.close();
        } else {
            duk_push_false(ctx);
        }
    }
    
    return 1;
}

duk_ret_t read_from_sd(duk_context *ctx) {
    if(duk_is_string(ctx, 0)) {
        File file = open(duk_get_string(ctx, 0), "r");
        if(!file) {
            duk_push_false(ctx);
        } else {
            duk_push_string(ctx, file.readString().c_str());
        }
    } else {
        duk_push_string(ctx, "");
    }
    return 1;
}

void init_js_storage(duk_context *ctx) {
    duk_push_c_function(ctx, write_to_sd, 2);
    duk_put_global_string(ctx, "write_to_sd");
    duk_push_c_function(ctx, read_from_sd, 1);
    duk_put_global_string(ctx, "read_from_sd");
}