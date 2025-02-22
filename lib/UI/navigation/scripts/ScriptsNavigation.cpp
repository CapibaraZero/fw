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

#include <list>
#include "gui.hpp"
#include "pages/FileBrowser/FileBrowserPage.hpp"
#include "posixsd.hpp"
#include "sdcard_helper.hpp"
#include "../navigation.hpp"
#include "../../../../include/debug.h"
#include "AppsJS.hpp"
#include "../../pages/DummyPage.hpp"

static Gui *_gui;
std::list<std::string> scripts_files;
static FileBrowserPage *file_browser_page;
static AppsJS *js_runtime;
DummyPage *dummy_page;

void goto_home_from_scripts() {
    init_main_gui();
    delete js_runtime;
    js_runtime = nullptr;
    file_browser_page = nullptr;
}

void run_script(const char *path) {
    File file = open(("/scripts/" + (String)path).c_str(), "r");
    if (!file) {
        LOG_ERROR("Failed to open file");
        return;
    }
    _gui->set_current_page(dummy_page, false);
    js_runtime->run_script(file.readString().c_str());
}

void goto_scripts_ui() {
    dummy_page = new DummyPage(0, 0, 0, _gui->get_screen());
    scripts_files = list_dir(open("/scripts", "r"));
    _gui->reset();
    file_browser_page =
        new FileBrowserPage(scripts_files.size() + 1, 1, 1, _gui->get_screen());
    file_browser_page->display("Scripts Browser", &scripts_files,
                                run_script, goto_home_from_scripts);
    _gui->set_current_page(file_browser_page, false);
}

void init_scripts_navigation(Gui *gui) { 
    _gui = gui; 
    js_runtime = new AppsJS();
}