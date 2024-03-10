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

#ifndef PAGE_H
#define PAGE_H

/* Virtual class that describes a capibaraZero page */
class Page {
 protected:
  GFXForms *screen;

 public:
  virtual void display() = 0;
  virtual void up() = 0;
  virtual void down() = 0;
  virtual void left() = 0;
  virtual void right() = 0;
};

#endif