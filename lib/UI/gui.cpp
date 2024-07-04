/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2024 Andrea Canale.
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

#include "gui.hpp"

#include <list>

#include "../../include/device_info.h"
#include "GFXForms.hpp"
#include "i18n.hpp"
#include "i18n/main_page_keys.h"
#include "style.h"

void Gui::init_gui() {
#ifdef CONFIG_IDF_TARGET_ESP32S2
  current_page = new MainPage(5, 0, 4, screen, this);
#else
  current_page = new MainPage(6, 0, 4, screen, this);
#endif
  current_page->display();
}

void Gui::click_element() {
  current_page->click();
}

void Gui::up() {
  current_page->up();
}

void Gui::down() {
  current_page->down();
}

void Gui::left() {
  current_page->left();
}

void Gui::right() {
  current_page->right();
}