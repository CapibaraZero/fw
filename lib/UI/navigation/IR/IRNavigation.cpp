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

#include "../../../../include/pins.h"
#include "../navigation.hpp"
#include "ArduinoJson.h"
#include "fm.hpp"
#include "gui.hpp"
#include "ir_attacks.hpp"
#include "pages/FileBrowser/FileBrowserPage.hpp"
#include "pages/IR/IREmulateRC.hpp"
#include "pages/IR/IRListsProgress.hpp"
#include "pages/IR/IRMainPage.hpp"
#include "pages/IR/IRRecordSignalPage.hpp"
#include "posixsd.hpp"
#include "sdcard_helper.hpp"

static Gui *gui;

static IRMainPage *ir_main_page = nullptr;
IRRecordSignalPage *ir_record_signal_page = nullptr;
static IREmulateRC *ir_emulate_rc = nullptr;
IrFramework *ir_framework = nullptr;
static IRListsProgress *ir_list_progress = nullptr;
static FileBrowserPage *file_browser_page = nullptr;

TaskHandle_t ir_record_task_handle = NULL;

void goto_ir_gui() {
  gui->reset();
  ir_main_page = new IRMainPage(3, 0, 1, gui->get_screen());
  gui->set_current_page(ir_main_page);
}

void ir_goto_home() {
  init_main_gui();
  ir_main_page = nullptr;
  delete ir_framework;
  ir_framework = nullptr;
}

void goto_ir_record_signal_page() {
  gui->reset();
  ir_record_signal_page =
      new IRRecordSignalPage(1, 1, 0, gui->get_screen());
  gui->set_current_page(ir_record_signal_page);
  ir_record_task_handle = ir_record_signal(ir_record_signal_page, ir_framework);
}

void save_record_to_sd() {
  Serial.println("Saving to SD");
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
  goto_ir_gui();
}

void stop_ir_record() {
  vTaskDelete(ir_record_task_handle);
  ir_record_task_handle = NULL;
  goto_ir_gui();
}

#include <list>

static std::list<string> ir_signal_files;
static TaskHandle_t list_sender_task_handle;

void send_signal(const char *path) {
  File rc_file = open("/IR/signals/" + (String)path, "r");
  JsonDocument *signal = new JsonDocument();
  deserializeJson(*signal, rc_file);
  if (signal->is<JsonArray>()) {
    gui->reset();
    ir_list_progress = new IRListsProgress(1, 1, 0, gui->get_screen());
    gui->set_current_page(ir_list_progress, true, false);
  }
  ir_send_signal(ir_framework, signal, ir_list_progress,
                 &list_sender_task_handle);
}

void stop_list_sender() {
  vTaskDelete(list_sender_task_handle);
  gui->reset();
  gui->set_current_page(file_browser_page, true, false);
}

static std::list<string> ir_rc_files;
JsonDocument rc_signals;

void goto_ir_rc_emulator(const char *path) {
  gui->reset();
  File rc_file = open("/IR/signal_rc/" + (String)path, "r");
  deserializeJson(rc_signals, rc_file);
  const char *cmds[rc_signals.size()];
  for (size_t i = 0; i < rc_signals.size(); i++) {
    cmds[i] = rc_signals[i]["name"].as<const char *>();
  }
  ir_emulate_rc =
      new IREmulateRC(rc_signals.size(), 0, 1, gui->get_screen());
  ir_emulate_rc->display(cmds, rc_signals.size());
  gui->set_current_page(ir_emulate_rc, false);
}

void goto_ir_rc_browser() {
  ir_rc_files = list_dir(open("/IR/signal_rc", "r"));
  gui->reset();
  file_browser_page =
      new FileBrowserPage(ir_rc_files.size() + 1, 1, 1, gui->get_screen());
  file_browser_page->display("IR RC Emulator", &ir_rc_files,
                             goto_ir_rc_emulator, goto_ir_gui);
  gui->set_current_page(file_browser_page, false);
}

void emulate_ir_rc() {
  size_t current_signal_index = ir_emulate_rc->get_current_element();
  JsonDocument current_signal = rc_signals[current_signal_index];
  ir_send_signal(ir_framework, &current_signal);
}

void go_back_to_ir_browser() {
  gui->reset();
  gui->set_current_page(file_browser_page, true, false);
}

void goto_ir_send() {
  ir_signal_files = list_dir(open("/IR/signals", "r"));
  gui->reset();
  file_browser_page = new FileBrowserPage(ir_signal_files.size() + 1, 1, 1,
                                          gui->get_screen());
  file_browser_page->display("IR File Browser", &ir_signal_files, send_signal,
                             goto_ir_gui);
  gui->set_current_page(file_browser_page, false);
}

void init_ir_navigation(Gui *_gui) {
  gui = _gui;
  ir_framework = new IrFramework(IR_RECEIVER_PIN, IR_EMITTER_PIN);
  // TODO: Delete std::list
}