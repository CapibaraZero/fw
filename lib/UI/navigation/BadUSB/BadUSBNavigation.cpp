#include <list>

#include "../../../../include/debug.h"
#include "../../i18n/BadUSB/badusb_keys.h"
#include "../navigation.hpp"
#include "gui.hpp"
#include "pages/FileBrowser/FileBrowserPage.hpp"
#include "parser.hpp"
#include "posixsd.hpp"
#include "sdcard_helper.hpp"
#include "usb_hid/USBHid.hpp"

static Gui *_gui;
std::list<std::string> files;
static FileBrowserPage *file_browser_page;

extern USBHid hid;  // From DuckyESP

extern FILE *yyin;
void badusb_selection_handler(const char *path) {
  FILE *file = fopen(("/sd/ducky/" + (String)path).c_str(), "r");
  if (!file) {
    _gui->show_error_page("Failed to open file");
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
  file_browser_page = nullptr;  // Deleted in init_main_gui()
}

void goto_badusb_gui() {
#ifdef ARDUINO_NANO_ESP32
  Serial.end();
#endif
  // Begin is performed in USBHid class(setting layout or by default)
  files = list_dir(open("/ducky", "r"));
  _gui->reset();
  file_browser_page =
      new FileBrowserPage(files.size() + 1, 1, 1, _gui->get_screen());
  file_browser_page->display("BadUSB Payload Browser", &files,
                             badusb_selection_handler, goto_home_from_badusb);
  _gui->set_current_page(file_browser_page, false);
}

void init_badusb_navigation(Gui *__gui) { _gui = __gui; }