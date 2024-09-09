
#include "fm.hpp"
#include "gui.hpp"
#include "../../../../include/pins.h"
#include "pages/IR/IRMainPage.hpp"
#include "pages/IR/IREmulateRC.hpp"
#include "pages/IR/IRRecordSignalPage.hpp"
#include "pages/FileBrowser/FileBrowserPage.hpp"
#include "../navigation.hpp"
#include "ir_attacks.hpp"
#include "ArduinoJson.h"
#include "posixsd.hpp"
#include "sdcard_helper.hpp"

static Gui *gui;

static IRMainPage *ir_main_page = nullptr;
IRRecordSignalPage *ir_record_signal_page = nullptr;
static IREmulateRC *ir_emulate_rc = nullptr;
static IrFramework *ir_framework = nullptr;
static FileBrowserPage *file_browser_page = nullptr;

void goto_ir_gui() {
    gui->reset();
    ir_main_page = new IRMainPage(3, 0, 1, gui->get_screen(), gui);
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
    ir_record_signal_page = new IRRecordSignalPage(1, 1, 0, gui->get_screen(), gui);
    gui->set_current_page(ir_record_signal_page);
    ir_record_signal(ir_record_signal_page, ir_framework);
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
    for (size_t i = 0; i < signal.raw_len; i++)
    {
        raw_data.add(signal.decodedRawDataArray[i]);
    }
    doc.shrinkToFit();
    File res = open("/IR/signals/" + (String)millis() + ".json", "w");
    serializeJsonPretty(doc, res);
    res.close();
    goto_ir_gui();
}

#include <list>

static std::list<string> ir_signal_files;
void send_signal(const char *path) {
    ir_send_signal(ir_framework, ("/IR/signals/" + (String)path).c_str());
}

static std::list<string> ir_rc_files;
JsonDocument rc_signals;

void goto_ir_rc_emulator(const char *path) {
    gui->reset();
    File rc_file = open("/IR/signal_rc/" + (String)path, "r");
    deserializeJson(rc_signals, rc_file);
    const char* cmds[rc_signals.size()];
    for (size_t i = 0; i < rc_signals.size(); i++)
    {
        cmds[i] = rc_signals[i]["name"].as<const char*>();
    }
    ir_emulate_rc = new IREmulateRC(rc_signals.size(), 0,1, gui->get_screen(), gui);
    ir_emulate_rc->display(cmds, rc_signals.size());
    gui->set_current_page(ir_emulate_rc, false);
}

void goto_ir_rc_browser() {
    gui->reset();
    ir_rc_files = list_dir(open("/IR/signal_rc", "r"));
    file_browser_page = new FileBrowserPage(ir_rc_files.size() + 1, 1, 1 , gui->get_screen(), gui);
    file_browser_page->display("IR RC Emulator", &ir_rc_files, goto_ir_rc_emulator, goto_ir_gui);
    gui->set_current_page(file_browser_page, false);
}

void emulate_ir_rc() {
    size_t current_signal_index = ir_emulate_rc->get_current_element();
    JsonDocument current_signal = rc_signals[current_signal_index];
    ir_send_signal(ir_framework, current_signal);
}

void goto_ir_send() {
    gui->reset();
    ir_signal_files = list_dir(open("/IR/signals", "r"));
    file_browser_page = new FileBrowserPage(ir_signal_files.size() + 1, 1, 1,gui->get_screen(), gui); 
    file_browser_page->display("IR File Browser", &ir_signal_files, send_signal, goto_ir_gui);
    gui->set_current_page(file_browser_page, false);
}

void init_ir_navigation(Gui *_gui) {
    gui = _gui;
    ir_framework = new IrFramework(IR_RECEIVER_PIN, IR_EMITTER_PIN);
}