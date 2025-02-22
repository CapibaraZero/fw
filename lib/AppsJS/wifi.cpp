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
#include "wifi_attack.hpp"
#include "posixsd.hpp"
#include "duktape.h"

extern WifiAttack wifiAttack;

duk_ret_t js_wifi_scan(duk_context *ctx) {
    wifiAttack.scan();
    duk_push_string(ctx, wifiAttack.scan_to_str().c_str());
    return 1;
}

duk_ret_t js_wifi_sniff(duk_context *ctx) {
    if(duk_get_top(ctx) == 2) {
        if(duk_is_number(ctx, 0)) {
           // File sniff_file = open(duk_to_string(ctx, 1), "w");
            wifiAttack.sniff(duk_to_int(ctx, 0), get_current_fs());
        }
    }
    return 0;
}

duk_ret_t js_wifi_sniff_bssid(duk_context *ctx) {
    // TODO
    return 0;
}

duk_ret_t js_wifi_sniffer_stop(duk_context *ctx) {
    wifiAttack.stop_sniff();
    return 0;
}

void init_js_wifi(duk_context *ctx) {
    duk_push_c_function(ctx, js_wifi_scan, 0);
    duk_put_global_string(ctx, "wifi_scan");
    duk_push_c_function(ctx, js_wifi_sniff, 1);
    duk_put_global_string(ctx, "wifi_sniff");
    duk_push_c_function(ctx, js_wifi_sniff_bssid, 0);
    duk_put_global_string(ctx, "wifi_sniff_bssid");
    duk_push_c_function(ctx, js_wifi_sniffer_stop, 0);
    duk_put_global_string(ctx, "wifi_sniffer_stop");
}