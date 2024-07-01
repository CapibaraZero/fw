#include "gui.hpp"
#include "subghz_attacks.hpp"
#include "../../../../include/pins.h"
#include "../navigation.hpp"
#include "fm.hpp"
#include "sdcard_helper.hpp"
#include "posixsd.hpp"
#include "ArduinoJson.h"

static Gui *gui;
SubGHZ *subghz_module = nullptr;

void goto_subghz_gui() {
  Serial.println("GOTO SUBGHZ");
  gui->reset();
  gui->set_current_position(0);
  gui->init_subghz_gui();
}

void start_frequency_analyzer() {
  gui->reset();
  gui->set_current_position(0);
  gui->destroy_subghz_gui();
  gui->init_subghz_frequency_analyzer();
  frequency_analyzer_attack(subghz_module, gui);
}

void stop_frequency_analyzer() {
  stop_subghz_attack();
  gui->destroy_subghz_frequency_analyzer();
  subghz_module->stop_receive();
  init_main_gui();
}

void start_raw_record() {
  gui->reset();
  gui->set_current_position(0);
  gui->destroy_subghz_gui();
  gui->init_subghz_raw_record_ui();
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

  File file = open(((String)"/subghz/raw_signals/" + (String)millis() + (String)"_capture.json"), "w");
      Serial.println("Saving file14");
  serializeJsonPretty(doc, file);
    Serial.println("Saving file4");

  file.close();
}

void stop_subghz_raw_record() {
  stop_subghz_attack();
  gui->destroy_subghz_raw_record_ui();
  init_main_gui();
  make_dump_file();
  subghz_module->stop_receive();
}

std::list<string> subghz_files;

void start_subghz_emulation(int pos) {
  gui->destroy_file_browser_gui();
  if(pos == subghz_files.size()) {
    init_main_gui();
    return;
  }
  std::list<std::string>::iterator selected_file = subghz_files.begin();
  std::advance(selected_file, pos);
  Serial.println(selected_file->c_str());
  gui->reset();
  gui->set_current_position(0); 
  gui->destroy_subghz_gui();
  gui->init_subghz_sender();
  start_subghz_emulation_attack(subghz_module, gui, ("/subghz/raw_signals/" + (String)selected_file->c_str()).c_str());
  gui->destroy_subghz_sender();
  init_main_gui();
}

void subghz_sender_file_browser() {
  gui->reset();
  gui->set_current_position(0);
  gui->destroy_subghz_gui();
  subghz_files = list_dir(open("/subghz/raw_signals", "r"));;
  gui->init_file_browser_gui("SubGHZ file browser", &subghz_files, false);
}

/* Avoid linker error */
void goto_home_from_subghz() {
  gui->destroy_subghz_gui();
  init_main_gui();
}

void subghz_submenu_handler(int pos) {
  switch (pos)
  {
  case 0:
    start_frequency_analyzer();
    break;
  case 1:
    start_raw_record();
    break;
  case 2:
    subghz_sender_file_browser();
    break;
  case 3:
    goto_home_from_subghz();
    break;
  default:
    break;
  }
}

void init_subghz_navigation(Gui *_gui) {
    gui = _gui;
    subghz_module = new SubGHZ(SD_CARD_SCK, SD_CARD_MISO, SD_CARD_MOSI, SX1276_NSS, SX1276_DIO1, SX1276_DIO2);
}