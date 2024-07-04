#include <list>

#include "gui.hpp"
#include "parser.hpp"
#include "posixsd.hpp"
#include "sdcard_helper.hpp"
#include "usb_hid/USBHid.hpp"
#include "../../../../include/debug.h"
#include "../../i18n/BadUSB/badusb_keys.h"
#include "../navigation.hpp"
#include "pages/FileBrowser/FileBrowserPage.hpp"

static Gui *_gui;
std::list<std::string> files;
static FileBrowserPage *file_browser_page;

extern USBHid hid;  // From DuckyESP

extern FILE *yyin;
void badusb_selection_handler(const char *path) {
  FILE *file = fopen(("/sd/ducky/" + (String)path).c_str(), "r");
  if (!file) {
    LOG_ERROR("Failed to open file");
    return;
  }
  yyin = file;
  yyparse();
  fclose(file);
}

void goto_home_from_badusb() {
    hid.end();
    #ifdef ARDUINO_NANO_ESP32
    Serial.begin(115200);
    #endif
    init_main_gui();
    delete file_browser_page;
    file_browser_page = nullptr;
}

void goto_badusb_gui() {
#ifdef ARDUINO_NANO_ESP32
  Serial.end();
#endif
  hid.begin();
  files = list_dir(open("/ducky", "r"));
  _gui->reset();
  file_browser_page = new FileBrowserPage(files.size() + 1, 1, 1, _gui->get_screen(), _gui);
  file_browser_page->display("BadUSB Payload Browser", &files, badusb_selection_handler, goto_home_from_badusb);
}

void init_badusb_navigation(Gui *__gui) { _gui = __gui; }