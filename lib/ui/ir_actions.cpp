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

TaskHandle_t ir_record_task_handle = NULL;
TaskHandle_t list_sender_task_handle = NULL;
IrFramework *ir_framework = nullptr;

extern "C" void action_go_to_ir_page(lv_event_t *e) {
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