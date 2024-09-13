
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

#include "SubGHZSender.hpp"

#include "../../i18n.hpp"
#include "gui.hpp"

SubGHZSender::~SubGHZSender() {
  delete current_frequency;
  delete current_modulation;
  delete current_bw;
  delete current_deviation;
}

void SubGHZSender::display() {
  grid = new Grid(screen, 4, 1);
  grid->set_y_spacing(30);
  current_frequency = new Text(screen, ST77XX_WHITE, "Frequency: 0 MHz");
  current_modulation = new Text(screen, ST77XX_WHITE, "Modulation: ");
  current_bw = new Text(screen, ST77XX_WHITE, "Bandwidth: ");
  current_deviation = new Text(screen, ST77XX_WHITE, "Deviation: ");
  grid->add(current_frequency);
  grid->add(current_modulation);
  grid->add(current_bw);
  grid->add(current_deviation);
  grid->display();
}