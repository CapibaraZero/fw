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
#include <map>
#include "Widget.hpp"
#include "Text.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include <GFXForms.hpp>
#include "gui.hpp"
#include "../UI/pages/DummyPage.hpp"
#include "../../include/debug.h"
#include "navigation/navigation.hpp"

extern Gui *main_gui;
extern DummyPage *dummy_page;

/* 
    Params:
        - Text color
        - Text str
        - Font size
        - Text wrap
        - X position of text
        - Y position of text
        - Display
*/
duk_ret_t create_text_widget(duk_context *ctx) {
    if(duk_get_top(ctx) == 6) {
        main_gui->reset();
        Text *txt = (Text *)malloc(sizeof(Text));
        txt = new Text(main_gui->get_screen(), duk_get_int(ctx, 0), duk_get_string(ctx, 1), duk_get_int(ctx, 2), true, duk_get_int(ctx, 3), duk_get_int(ctx, 4));
        duk_idx_t widget_id = duk_push_object(ctx);
        duk_push_pointer(ctx, txt);
        duk_put_prop_string(ctx, widget_id, "ptr");
        if(duk_get_boolean(ctx, 6))
            txt->display();
    } else {
        LOG_ERROR("Not enough argument for create_text_widget");
    }
    return 1;
}

// params: Text
duk_ret_t set_text(duk_context *ctx) {
    Text *txt = static_cast<Text *>(duk_get_pointer(ctx, 0));
    txt->set_text(duk_get_string(ctx, 1));
    return 0;
}

// params: x,y
duk_ret_t text_set_position(duk_context *ctx) {
    Text *txt = static_cast<Text *>(duk_get_pointer(ctx, 0));
    txt->set_pos(duk_get_int(ctx, 1), duk_get_int(ctx, 2));
    return 0;
}

// params: rows, cols
duk_ret_t create_grid_widget(duk_context *ctx) {
    if(duk_get_top(ctx) == 2) {
        dummy_page->set_pos_limit(duk_get_int(ctx, 0) - 1);
        dummy_page->create_grid(duk_get_int(ctx, 0), duk_get_int(ctx, 1));
    }else {
        LOG_ERROR("Not enough argument for create_grid_widget()");
    }
    return 1;
}

// Params: Pointer to widget(widget.ptr on JS)
duk_ret_t grid_add_widget(duk_context *ctx) {
    if(duk_get_top(ctx) == 1) {
        Widget *widget = static_cast<Widget *>(duk_get_pointer(ctx, 0));
        dummy_page->grid_add_widget(widget);
    } else {
        LOG_ERROR("Not enough argument for grid_add_widget()");
    }
    return 0;
}

duk_ret_t grid_display(duk_context *ctx) {
    dummy_page->display();
    return 0;
}

// Params: position, status(selected or not selecte)
duk_ret_t grid_set_selected(duk_context *ctx) {
    if(duk_get_top(ctx) == 2) {
        dummy_page->set_selected(duk_get_int(ctx, 0), duk_get_boolean(ctx, 1));
    } else {
        LOG_ERROR("Not enough argument for grid_set_selected()");
    }
    return 0;
}

// Params: Y spacing
duk_ret_t grid_set_y_spacing(duk_context *ctx) {
    if(duk_get_top(ctx) == 1) {
        dummy_page->grid_set_y_spacing(duk_get_int(ctx, 0));
    } else {
        LOG_ERROR("Not enough argument for grid_set_selected()");
    }
    return 0;
}

// Params: Space between
duk_ret_t grid_set_space_between(duk_context *ctx) {
    if(duk_get_top(ctx) == 1) {
        dummy_page->grid_set_space_between(duk_get_int(ctx, 0));
    } else {
        LOG_ERROR("Not enough argument for grid_set_selected()");
    }
    return 0;
}

// Params: text, font_size, font_color, height, rect_color, unique id
// When list is clicked, GUI calls a callback in JS that must be wrote like this global.uniqueid_on_click = function() {}
duk_ret_t create_list_widget(duk_context *ctx) {
    if(duk_get_top(ctx) == 6) {
        duk_idx_t widget_id = duk_push_object(ctx);
        main_gui->reset();
        List *list = (List *)malloc(sizeof(List));
        String id = duk_get_string(ctx, 5);
        list = new List(main_gui->get_screen(), duk_get_string(ctx, 0), duk_get_int(ctx, 1), duk_get_int(ctx, 2), duk_get_int(ctx, 3), duk_get_int(ctx, 4), [ctx, id](){
            if(duk_get_global_string(ctx, (id + "_on_click").c_str()) != 0) {
                duk_int_t rc = duk_pcall(ctx, 0); 
                if (rc != DUK_EXEC_SUCCESS) {
                    Serial.println("Error");
                    Serial.println(duk_to_string(ctx, -1));
                }
                duk_pop(ctx);
            } else {
                Serial.println("on_click method not found");
            }
        });
        duk_push_pointer(ctx, list);
        duk_put_prop_string(ctx, widget_id, "ptr");
    }
    return 1;
}

duk_ret_t goto_main_gui(duk_context *ctx) {
    init_main_gui();
    duk_destroy_heap(ctx);
    return 0;
}

// Expose global object(https://wiki.duktape.org/howtoglobalobjectreference)
const char *global_snippet = R"(if (typeof global === 'undefined') { 
    (function () {
        var global = new Function('return this;')();
        Object.defineProperty(global, 'global', {
            value: global,
            writable: true,
            enumerable: false,
            configurable: true
        });
    })();
}
)";

void init_gui_js(duk_context *ctx) {

    // Text function
    duk_push_c_function(ctx, create_text_widget, 6);
    duk_put_global_string(ctx, "create_text_widget");
    duk_push_c_function(ctx, set_text, 2);
    duk_put_global_string(ctx, "set_text");
    duk_push_c_function(ctx, text_set_position, 3);
    duk_put_global_string(ctx, "text_set_position");

    // Grid function
    duk_push_c_function(ctx, create_grid_widget, 2);
    duk_put_global_string(ctx, "create_grid_widget");
    duk_push_c_function(ctx, grid_add_widget, 1);
    duk_put_global_string(ctx, "grid_add_widget");
    duk_push_c_function(ctx, grid_display, 0);
    duk_put_global_string(ctx, "grid_display");
    duk_push_c_function(ctx, grid_set_selected, 2);
    duk_put_global_string(ctx, "grid_set_selected");
    duk_push_c_function(ctx, grid_set_y_spacing, 1);
    duk_put_global_string(ctx, "grid_set_y_spacing");
    duk_push_c_function(ctx, grid_set_space_between, 1);
    duk_put_global_string(ctx, "grid_set_space_between");

    // List function
    duk_push_c_function(ctx, create_list_widget, 6);
    duk_put_global_string(ctx, "create_list_widget");
    duk_eval_string(ctx, global_snippet);

    duk_push_c_function(ctx, goto_main_gui, 0);
    duk_put_global_string(ctx, "goto_main_gui");
}