#include "../../../../include/pins.h"
#include "../navigation.hpp"
#include "ArduinoJson.h"
#include "fm.hpp"
#include "gui.hpp"
#include "posixsd.hpp"
#include "sdcard_helper.hpp"
#include "subghz_attacks.hpp"
#include "pages/SubGHZ/SubGHZPage.hpp"
#include "pages/SubGHZ/SubGHZFrequencyAnalyzerPage.hpp"
#include "pages/SubGHZ/SubGHZRAWRecordPage.hpp"
#include "pages/SubGHZ/SubGHZSender.hpp"
#include "pages/FileBrowser/FileBrowserPage.hpp"

static Gui *gui;
SubGHZ *subghz_module = nullptr;
static SubGHZPage *subghz_page = nullptr;
static SubGHZFrequencyAnalyzerPage *subghz_frequency_analyzer_page = nullptr;
static SubGHZRAWRecordPage *subghz_raw_record_page = nullptr;
static SubGHZSender *subghz_sender_page = nullptr;
static FileBrowserPage *file_browser_page = nullptr;

void goto_subghz_gui() {
    Serial.println("GOTO SUBGHZ");
    gui->reset();
    subghz_page = new SubGHZPage(3, 0, 1, gui->get_screen(), gui);
    gui->set_current_page(subghz_page);
    subghz_page->display();
}

static void destroy_subghz_gui() {
    delete subghz_page;
    subghz_page = nullptr;
}

void start_frequency_analyzer() {
    gui->reset();
    destroy_subghz_gui();
    subghz_frequency_analyzer_page =
        new SubGHZFrequencyAnalyzerPage(2, 2, 0, gui->get_screen(), gui);
    gui->set_current_page(subghz_frequency_analyzer_page);
    subghz_frequency_analyzer_page->display();
    frequency_analyzer_attack(subghz_module, gui);
}

void stop_frequency_analyzer() {
    stop_subghz_attack();
    delete subghz_frequency_analyzer_page;
    subghz_frequency_analyzer_page = nullptr;
    subghz_module->stop_receive();
    init_main_gui();
}

void start_raw_record() {
    gui->reset();
    destroy_subghz_gui();
    subghz_raw_record_page =
        new SubGHZRAWRecordPage(1, 0, 0, gui->get_screen(), gui);
    gui->set_current_page(subghz_raw_record_page);
    subghz_raw_record_page->display();
    raw_record_attack(subghz_module, gui);
}

void make_dump_file() {
    Serial.println("Saving file");
    extern std::vector<byte> raw_signal;
    DynamicJsonDocument doc(110 + (32 * raw_signal.size()));
    doc["frequency"] = subghz_module->get_frequency();
    doc["bandwidth"] = subghz_module->get_bw();
    doc["deviation"] = subghz_module->get_deviation();
    doc["data_length"] = raw_signal.size();
    JsonArray data = doc.createNestedArray("data");
    Serial.println("Saving file");
    for (byte b : raw_signal) {
        data.add(b);
    }
    Serial.println("Saving file");

    File file = open(((String) "/subghz/raw_signals/" + (String)millis() +
                      (String) "_capture.json"),
                     "w");
    Serial.println("Saving file14");
    serializeJsonPretty(doc, file);
    Serial.println("Saving file4");

    file.close();
}

void stop_subghz_raw_record() {
    stop_subghz_attack();
    delete subghz_raw_record_page;
    subghz_raw_record_page = nullptr;
    init_main_gui();
    make_dump_file();
    subghz_module->stop_receive();
}

std::list<string> subghz_files;

void start_subghz_emulation(const char *path) {
    delete file_browser_page;
    file_browser_page = nullptr;
    if (path == "Exit") {
        init_main_gui();
        return;
    }
    gui->reset();
    destroy_subghz_gui();
    subghz_sender_page = new SubGHZSender(0, 0, 0, gui->get_screen(), gui);
    subghz_sender_page->display();
    start_subghz_emulation_attack(
        subghz_module, gui,
        ("/subghz/raw_signals/" + (String)path).c_str());
    delete subghz_sender_page;
    subghz_sender_page = nullptr;
    init_main_gui();
}

/* Avoid linker error */
void goto_home_from_subghz() {
    destroy_subghz_gui();
    init_main_gui();
}

void subghz_sender_file_browser() {
    gui->reset();
    destroy_subghz_gui();
    subghz_files = list_dir(open("/subghz/raw_signals", "r"));
    file_browser_page = new FileBrowserPage(subghz_files.size() + 1, 1, 1,gui->get_screen(), gui); 
    file_browser_page->display("SubGHZ File Browser", &subghz_files, start_subghz_emulation, goto_home_from_subghz);
}

void set_subghz_freqeuncy(float freq) {
    subghz_frequency_analyzer_page->set_frequency(freq);
}
void set_subghz_rssi(int rssi) {
    subghz_frequency_analyzer_page->set_rssi(rssi);
}
void set_subghz_raw_record_freq(float freq) {
    subghz_raw_record_page->set_frequency(freq);
}
void set_subghz_raw_record_rssi(float rssi) {
    subghz_raw_record_page->set_rssi(rssi);
}

void set_subghz_sender_freq(float freq) {
    subghz_sender_page->set_frequency(freq);
}
void set_subghz_sender_bandwidth(float bandwidth) {
    subghz_sender_page->set_bandwidth(bandwidth);
}
void set_subghz_sender_deviation(float deviation) {
    subghz_sender_page->set_deviation(deviation);
}
void set_subghz_sender_modulation(int modulation) {
    subghz_sender_page->set_modulation(modulation);
}

void init_subghz_navigation(Gui *_gui) {
    gui = _gui;
    subghz_module = new SubGHZ(SD_CARD_SCK, SD_CARD_MISO, SD_CARD_MOSI,
                               SX1276_NSS, SX1276_DIO1, SX1276_DIO2);
}