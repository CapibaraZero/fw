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
#include "../../../../include/debug.h"

#ifndef NetworkAttacks_PAGE_H
#define NetworkAttacks_PAGE_H

class NetworkAttacksPage : public Page {
 private:
  List *dhcpglutton;
  List *evilportal;
  Grid *net_attacks_grid;

 public:
  NetworkAttacksPage(GFXForms *_screen);
  ~NetworkAttacksPage();
  void display();
  void click(int pos, void callback()) {
    net_attacks_grid->click(pos, callback);
  };
  void set_selected(int pos, bool status) {
    LOG_INFO("Set selected");
    net_attacks_grid->set_selected(pos, status);
  };
  void up() {};
  void down() {};
  void left() {};
  void right() {};
};

#endif
