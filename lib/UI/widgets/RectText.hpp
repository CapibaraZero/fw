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

#include <Arduino.h>

#include "GFXForms.hpp"
#include "Grid.hpp"
#include "Rect.hpp"
#include "Text.hpp"

#ifndef RECT_TEXT_H
#define RECT_TEXT_H

class RectText : public Widget {
 private:
  Rect *box;
  Text *text_widget;
  Grid *container;

 public:
  RectText(GFXForms *display, const char *text, int font_size,
           uint16_t font_color, int _heigth, int radius, uint16_t rect_color,
           std::function<void()> _cb);
  ~RectText();
  void set_pos(int _x, int _y) {
    x = _x;
    y = _y;
    container->set_pos(_x, _y);
  };
  void set_color(uint16_t _color) {};
  void display() { container->display(); };
  void set_dimension(int _width, int _heigth) {
    width = _width;
    heigth = _heigth;
    container->set_dimension(_width, _heigth);
  };
  void set_selected(bool _selected) {
    selected = _selected;
    if (selected)
      box->fill(ST77XX_BLUE);
    else
      box->fill(ST77XX_BLACK);
  };
  void click() {
    Serial.println("Widget clicked");
    cb();
  };
  void click(void callback()) { callback(); }
};
#endif