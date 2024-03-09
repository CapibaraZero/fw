#include "gui.hpp"
#include "posixsd.hpp"
#include "sdcard_helper.hpp"
#include <list>
#include "parser.hpp"

static Gui *_gui;
std::list<std::string> files;

void goto_badusb_gui() {
    files = list_dir(open("/ducky", "r"));
    _gui->reset();
    _gui->set_current_position(1);
    _gui->init_badusb_browser_gui(&files);
    _gui->set_position_limit(files.size() + 1);
}

extern FILE *yyin;
void badusb_selection_handler(int pos) {
    if(pos == files.size() + 1) {   // Means return to main menu
        _gui->reset();
        _gui->destroy_badusb_browser_gui();
        _gui->init_gui();
        _gui->set_current_position(0);
        _gui->set_selected_widget(0, true);
        return;
    }
    auto selected_file = files.begin();
    std::advance(selected_file, pos - 1);
    Serial0.printf("Selected file: %s\n", selected_file->c_str());
    FILE *file = fopen(("/sd/ducky/" + *selected_file).c_str(), "r");
    if(!file) {
        Serial0.println("Failed to open file");
        return;
    }
    yyin = file;
    yyparse();
    fclose(file);
}

void init_badusb_navigation(Gui *__gui) {
    _gui = __gui;
}