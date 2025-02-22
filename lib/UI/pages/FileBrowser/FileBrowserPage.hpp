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

#include <list>

#include "../Page.hpp"
#include "Grid.hpp"
#include "List.hpp"
#include "Text.hpp"

#ifndef FILE_BROWSER_PAGE_H
#define FILE_BROWSER_PAGE_H

class FileBrowserPage : public Page {
 private:
  Text *title;
  List *go_back;

 public:
  FileBrowserPage(uint8_t _position_limit, uint8_t _lower_limit,
                  uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~FileBrowserPage();
  void display();
  void display(const char *text, std::list<std::string> *files,
               std::function<void(const char *)> list_cb,
               std::function<void()> go_back_cb);
  void click(int pos, void callback()) { grid->click(pos, callback); };
  void set_selected(int pos, bool status) { grid->set_selected(pos, status); };
  void cleanup() { delete grid; };
};

#endif
