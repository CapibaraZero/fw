
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

#include "Page.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "widgets/RectText.hpp"

#ifndef DUMMY_PAGE_H
#define DUMMY_PAGE_H

class DummyPage : public Page {
 private:
//   List *go_back;

 public:
  DummyPage(uint8_t _position_limit, uint8_t _lower_limit,
              uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~DummyPage() {};
  void display() {
    grid->display();
  };
  void set_selected(int pos, bool status) { grid->set_selected(pos, status); };
  // void click() {
  //   grid->click();
  // }
  void click(int pos, void callback()) { grid->click(pos, callback); };
  // void left() {};
  // void right() {};
  size_t get_current_element() { return grid->get_selected(); };
  void create_grid(size_t rows, size_t cols) {
    grid = new Grid(screen, rows, cols);
  }
  void grid_set_y_spacing(int y_spacing) {
    grid->set_y_spacing(y_spacing);
  }
  void grid_set_space_between(int space_between) {
    grid->set_space_between(space_between);
  }
  void grid_add_widget(Widget *widget) {
    grid->add(widget);
  }
  void set_pos_limit(size_t pos_limit) {
    position_limit = pos_limit;
    position_increment = 1;
  }
};

#endif
