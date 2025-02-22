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

#include "duktape.h"
#include "Arduino.h"
#include "usb_hid/USBHid.hpp" 
#include "SDBridge32.hpp"

static USBHid hid = USBHid();
static SDBridge32 msc = SDBridge32();

duk_ret_t init_badusb(duk_context *ctx) {
    Serial.end();
    hid.begin();
    return 0;
}

duk_ret_t stop_badusb(duk_context *ctx) {
    hid.end();
    return 0;
}

duk_ret_t init_msc(duk_context *ctx) {
    stop_badusb(ctx);
    switch(duk_get_top(ctx)) {
        case 0:
            msc.begin("CapibaraZero", "DuckyESP", "1.1.0");
            break;
        case 1:
            msc.begin(duk_get_string(ctx, 0), "DuckyESP", "1.1.0");
            break;
        case 2:
            msc.begin(duk_get_string(ctx, 0), duk_get_string(ctx, 1), "1.1.0");
            break;
        case 3:
            msc.begin(duk_get_string(ctx, 0), duk_get_string(ctx, 0), duk_get_string(ctx,2));
            break;
        default:
            break;
    }
    return 0;
}

duk_ret_t print_string(duk_context *ctx) {
    if(duk_get_top(ctx) != 1)
        return 0;
    hid.print_string(duk_get_string(ctx, 0));
    return 0;
}

duk_ret_t mouse_press(duk_context *ctx) {
    hid.mouse_click();
    return 0;
}

duk_ret_t mouse_set_coordinate(duk_context *ctx) {
    if(duk_get_top(ctx) != 2)
        return 0;
    int x = duk_get_int(ctx, 0);
    int y = duk_get_int(ctx, 1);

    hid.mouse_set_coordinate(x, y);
    return 0;
}

duk_ret_t release(duk_context *ctx) {
    if(duk_get_top(ctx) != 1)
        return 0;
    hid.release(duk_get_uint(ctx, 0));
    return 0;
}

duk_ret_t release_all(duk_context *ctx) {
    hid.release_all();
    return 0;
}

duk_ret_t press(duk_context *ctx) {
    if(duk_get_top(ctx) != 1)
        return 0;
    hid.press(duk_get_uint(ctx, 0));
    return 0;
}

duk_ret_t press_raw(duk_context *ctx) {
    if(duk_get_top(ctx) != 1)
        return 0;
    hid.press_raw(duk_get_uint(ctx, 0));
    return 0;
}

void init_js_badusb(duk_context *ctx) {
    duk_push_c_function(ctx, init_badusb, 0);
    duk_put_global_string(ctx, "init_badusb");
    duk_push_c_function(ctx, init_msc, 3);
    duk_put_global_string(ctx, "init_msc");
    duk_push_c_function(ctx, stop_badusb, 0);
    duk_put_global_string(ctx, "stop_badusb");
    duk_push_c_function(ctx, print_string, 1);
    duk_put_global_string(ctx, "print_string");
    duk_push_c_function(ctx, mouse_press, 1);
    duk_put_global_string(ctx, "mouse_press");
    duk_push_c_function(ctx, mouse_set_coordinate, 2);
    duk_put_global_string(ctx, "mouse_set_coordinate");
    duk_push_c_function(ctx, release, 1);
    duk_put_global_string(ctx, "release");
    duk_push_c_function(ctx, release_all, 0);
    duk_put_global_string(ctx, "release_all");
    duk_push_c_function(ctx, press, 1);
    duk_put_global_string(ctx, "press");
    duk_push_c_function(ctx, press_raw, 0);
    duk_put_global_string(ctx, "press_raw");
};