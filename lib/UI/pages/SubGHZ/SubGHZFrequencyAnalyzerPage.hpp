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

#ifndef SUBGHZ_FREQUENCY_ANALYZER_PAGE_H
#define SUBGHZ_FREQUENCY_ANALYZER_PAGE_H

class SubGHZFrequencyAnalyzerPage : public Page {
 private:
  Text *current_frequency;
  Text *current_rssi;
  List *stop;

 public:
  SubGHZFrequencyAnalyzerPage(uint8_t _position_limit, uint8_t _lower_limit,
                              uint8_t _position_increment, GFXForms *screen)
      : Page(_position_limit, _lower_limit, _position_increment, screen) {
        };
  ~SubGHZFrequencyAnalyzerPage();
  void display();

  void click(int pos, void callback()) { grid->click(pos, callback); };
  void set_selected(int pos, bool status) { grid->set_selected(pos, status); };
  void set_rssi(int rssi) { current_rssi->set_text("RSSI: " + String(rssi)); }
  void set_frequency(float frequency) {
    current_frequency->set_text("Frequency: " + String(frequency) + "MHz");
  }
};

#endif