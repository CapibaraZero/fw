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

#include "ui.h"
#include "IrFramework.hpp"
#include "ir_attacks.hpp"
#include "vars.h"
#include "posixsd.hpp"
#include "../../include/pins.h"
#include "ui_helper.hpp"

TaskHandle_t ir_record_task_handle = NULL;
TaskHandle_t list_sender_task_handle = NULL;
IrFramework *ir_framework = nullptr;

JsonDocument rc_signals;

extern "C" void action_go_to_ir_page(lv_event_t *e) {
    if(rc_signals.size() > 0)   // Cleanup old emulation data if necessary 
        rc_signals.clear();

    create_screen_ir_page();
    loadScreen(SCREEN_ID_IR_PAGE);
    if(ir_framework == nullptr)
        ir_framework = new IrFramework(IR_RECEIVER_PIN, IR_EMITTER_PIN);
}

extern "C" void action_go_to_ir_record_signal_page(lv_event_t *e) {
    set_var_ir_protocol("Waiting for signal...");   // Reset initial state
    set_var_ir_addr("");
    set_var_ir_cmd("");
    set_var_ir_len("");
    set_var_ir_retry(true); // Hide retry and save
    set_var_ir_save(true);

    create_screen_ir_record_signal_page();
    loadScreen(SCREEN_ID_IR_RECORD_SIGNAL_PAGE);

    ir_record_task_handle = ir_record_signal(ir_framework);
}

extern "C" void action_stop_ir_record(lv_event_t *e) {
    vTaskDelete(ir_record_task_handle);
    ir_record_task_handle = NULL;

    action_go_to_ir_page(e);
}

extern "C" void action_ir_save_record(lv_event_t *e) {
    RecordedSignal signal = ir_framework->get_decoded_signal();
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
    File res = open("/IR/signals/" + (String)millis() + ".json", "w");
    serializeJsonPretty(doc, res);
    res.close();

    action_go_to_ir_page(e);
}

extern "C" void action_ir_retry_record(lv_event_t *e) {
    set_var_ir_protocol("Waiting for signal...");   // Reset initial state
    set_var_ir_addr("");
    set_var_ir_cmd("");
    set_var_ir_len("");
    set_var_ir_retry(true); // Hide retry and save
    set_var_ir_save(true);

    ir_record_task_handle = ir_record_signal(ir_framework); // Start a new record
}

extern "C" void action_ir_send_signal(lv_event_t *e) {
    const char *path = (const char *)e->user_data;

    File rc_file = open("/IR/signals/" + (String)path, "r");
    JsonDocument *signal = new JsonDocument();
    deserializeJson(*signal, rc_file);
    if (signal->is<JsonArray>()) {
        create_screen_ir_emulate_list_page();
        loadScreen(SCREEN_ID_IR_EMULATE_LIST_PAGE);
    }
    ir_send_signal(ir_framework, signal, &list_sender_task_handle);
}

lv_obj_t *prepare_ir_page() {
    // Create initial page
    lv_obj_t *main_obj = lv_obj_create(0);
    objects.irrc_page = main_obj;
    lv_obj_set_pos(main_obj, 0, 0);
    lv_obj_set_size(main_obj, 320, 170);

    // Create container widget with Flex column property
    lv_obj_t *container_obj = lv_obj_create(main_obj);
    lv_obj_set_pos(container_obj, 0, 19);
    lv_obj_set_size(container_obj, 320, 151);
    lv_obj_set_style_pad_left(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(container_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(container_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(container_obj, LV_FLEX_FLOW_ROW_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);

    return container_obj;
}

void send_rc_signal(lv_event_t *e) {
    size_t current_signal_index = (size_t) e;

    JsonDocument current_signal = rc_signals[current_signal_index];
    ir_send_signal(ir_framework, &current_signal);
}

extern "C" void action_ir_open_rc(lv_event_t *e) {
    const char *path = (const char *)e->user_data;

    File rc_file = open("/IR/signal_rc/" + (String)path, "r");
    deserializeJson(rc_signals, rc_file);

    lv_obj_t *page = prepare_ir_page();

    for (size_t i = 0; i < rc_signals.size(); i++) {
      create_btn(rc_signals[i]["name"], page, send_rc_signal, (void *)i, 100, 50);
    }

    create_btn("Go back", page, action_go_to_ir_page, NULL);

    loadScreen(SCREEN_ID_IRRC_PAGE);
    tick_screen_irrc_page();
}
