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

#include "GFXForms.hpp"
#include "Grid.hpp"

#ifndef PAGE_H
#define PAGE_H

class Gui;

/* Virtual class that describes a capibaraZero page */
class Page {
 protected:
  GFXForms *screen;
  uint8_t position_limit = 0;
  uint8_t lower_limit = 0;
  uint8_t position_increment = 0;
  uint8_t current_position = 0;
  Grid *grid = nullptr;
  Page(uint8_t _position_limit, uint8_t _lower_limit,
       uint8_t _position_increment, GFXForms *_screen) {
    this->position_limit = _position_limit;
    this->lower_limit = _lower_limit;
    this->position_increment = _position_increment;
    this->current_position = _lower_limit;
    this->screen = _screen;
  }

 public:
  virtual ~Page() { delete grid; }
  virtual void display() = 0;
  virtual void up() {
    if (position_increment == 0) return;
    int tmp_current_position = current_position - position_increment;
    if (tmp_current_position <= position_limit &&
        tmp_current_position >= lower_limit) {
      grid->set_selected(current_position, false);
      current_position = tmp_current_position;
    }
    grid->set_selected(current_position, true);
  };
  virtual void down() {
    if (position_increment == 0) return;
    int tmp_current_position = current_position + position_increment;
    if (tmp_current_position <= position_limit) {
      grid->set_selected(current_position, false);
      current_position = tmp_current_position;
    }
    grid->set_selected(current_position, true);
  };
  virtual void left() {
#if ENCODER_NAVIGATION
    up();
#endif
  };
  virtual void right() {
#ifdef ENCODER_NAVIGATION
    down();
#endif
  };
  virtual void click() { grid->click(); };
};

#endif