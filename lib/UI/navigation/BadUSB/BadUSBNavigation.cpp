#include <list>

#include "gui.hpp"
#include "parser.hpp"
#include "posixsd.hpp"
#include "sdcard_helper.hpp"
#include "usb_hid/USBHid.hpp"
#include "../../../../include/debug.h"
#include "../../i18n/BadUSB/badusb_keys.h"

static Gui *_gui;
std::list<std::string> files;

extern USBHid hid;  // From DuckyESP

void goto_badusb_gui() {
#ifdef ARDUINO_NANO_ESP32
  Serial.end();
#endif
  hid.begin();
  files = list_dir(open("/ducky", "r"));
  _gui->reset();
  _gui->set_current_position(1);
  _gui->init_file_browser_gui(english_words->at(BADUSB_TITLE_KEY), &files, true);
  _gui->set_position_limit(files.size() + 1);
}

extern FILE *yyin;
void badusb_selection_handler(int pos) {
  if (pos == files.size() + 1) {  // Means return to main menu
    hid.end();
    _gui->reset();
    _gui->destroy_file_browser_gui();
    _gui->init_gui();
    _gui->set_current_position(0);
    _gui->set_selected_widget(0, true);
    return;
  }
  std::list<std::string>::iterator selected_file = files.begin();
  std::advance(selected_file, pos - 1);
  Serial.printf("Selected file: %s\n", selected_file->c_str());
  FILE *file = fopen(("/sd/ducky/" + *selected_file).c_str(), "r");
  if (!file) {
    LOG_ERROR("Failed to open file");
    return;
  }
  yyin = file;
  yyparse();
  fclose(file);
}

void init_badusb_navigation(Gui *__gui) { _gui = __gui; }