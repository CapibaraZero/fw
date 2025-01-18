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

#include "AppsJS.hpp"
#include "duktape.h"
#include "ble.hpp"
#include "io.hpp"
#include "ir.hpp"
#include "nfc.hpp"
#include "storage.hpp"
#include "timer.hpp"
#include "js_gui.hpp"

AppsJS::AppsJS() {
    ctx = duk_create_heap_default();
    init_js_ble(ctx);
    init_js_io(ctx);
    init_js_ir(ctx);
    init_js_nfc(ctx);
    init_js_storage(ctx);
    init_js_timer(ctx);
    init_gui_js(ctx);
}

AppsJS::~AppsJS() {
    duk_destroy_heap(ctx);
}
