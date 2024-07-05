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

#include "pages/Page.hpp"
#include "GFXForms.hpp"
#include "widgets/RectText.hpp"
#include "pages/main_page/MainPage.hpp"

#ifndef GUI_H
#define GUI_H

class Gui {
 private:
  GFXForms *screen;
  Page *current_page = nullptr;
  MainPage *main_page = nullptr;  // Never delete main_page since it's always necessary
 public:
  Gui(GFXForms *_screen) { screen = _screen; };
  ~Gui(){};
  GFXForms *get_screen() { return screen; }
  /// @brief Init main GUI
  void init_gui();

  /// @brief Click and element and call a function on click
  void click_element();
  /// @brief Clean the screen(fill black color)
  void reset() { screen->reset(); }

  void set_current_page(Page *page) {
    delete current_page;
    current_page = page;
  }

  /// @brief Generate arrrow-up event and propagate to current page
  void up();

  /// @brief Generate arrrow-down event and propagate to current page
  void down();

  /// @brief Generate arrrow-left event and propagate to current page
  void left();

  /// @brief Generate arrrow-right event and propagate to current page
  void right();
};

#endif
