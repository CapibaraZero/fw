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

#include "../Page.hpp"
#include "Grid.hpp"
#include "List.hpp"

#ifndef SUBGHZ_PAGE_H
#define SUBGHZ_PAGE_H

class SubGHZPage : public Page {
 private:
  List *SubGHZ_freq_analyzer;
  List *SubGHZ_sniff;
  List *SubGHZ_sender;
  List *SubGHZ_jammer;
  List *go_back;
  Grid *SubGHZ_grid;

 public:
  SubGHZPage(GFXForms *_screen);
  ~SubGHZPage();
  void display();
  void click(int pos, void callback()) { SubGHZ_grid->click(pos, callback); };
  void set_selected(int pos, bool status) {
    SubGHZ_grid->set_selected(pos, status);
  };
  void up() {};
  void down() {};
  void left() {};
  void right() {};
};

#endif