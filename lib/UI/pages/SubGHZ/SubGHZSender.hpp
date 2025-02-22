
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

#ifndef SUBGHZ_SENDER_PAGE_H
#define SUBGHZ_SENDER_PAGE_H

class SubGHZSender : public Page {
 private:
  Text *current_frequency;
  Text *current_modulation;
  Text *current_bw;
  Text *current_deviation;
  Text *bytes;

 public:
  SubGHZSender(uint8_t _position_limit, uint8_t _lower_limit,
               uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~SubGHZSender();
  void display();
  void click(int pos, void callback()) { grid->click(pos, callback); };
  void set_selected(int pos, bool status) { grid->set_selected(pos, status); };
  void set_frequency(int frequency) {
    current_frequency->set_text("Frequency: " + String(frequency) + "MHz");
  }
  void set_modulation(int modulation) {
    if (modulation == 0)
      current_modulation->set_text("Modulation: ASK");
    else if (modulation == 1)
      current_modulation->set_text("Modulation: FSK");
    else if (modulation == 2)
      current_modulation->set_text("Modulation: LoRA");
    else
      current_modulation->set_text("Modulation: UNKNOWN");
  }
  void set_bandwidth(int bandwidth) {
    current_bw->set_text("Bandwidth: " + String(bandwidth) + "KHz");
  }
  void set_deviation(int deviation) {
    current_deviation->set_text("Deviation: " + String(deviation) + "KHz");
  }
  void up() {};
  void down() {};
  void left() {};
  void right() {};
};

#endif