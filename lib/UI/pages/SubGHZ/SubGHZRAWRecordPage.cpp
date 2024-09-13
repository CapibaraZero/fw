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

#include "SubGHZRAWRecordPage.hpp"

#include "../../i18n.hpp"
#include "../../navigation/SubGHZ/SubGHZNavigation.hpp"
#include "gui.hpp"

SubGHZRAWRecordPage::~SubGHZRAWRecordPage() {
  delete current_frequency;
  delete current_rssi;
  delete current_lqi;
  delete stop;
}

void SubGHZRAWRecordPage::display() {
  grid = new Grid(screen, 3, 1);
  grid->set_y_spacing(30);
  current_frequency = new Text(screen, ST77XX_WHITE, "Frequency: 0 MHz");
  current_rssi = new Text(screen, ST77XX_WHITE, "RSSI: 0 dBm");
  current_lqi = new Text(screen, ST77XX_WHITE, "LQI: 0");
  stop = new List(screen, "Stop", 2, ST77XX_WHITE, 20, ST77XX_BLUE,
                  stop_subghz_raw_record);
  grid->add(current_frequency);
  grid->add(current_rssi);
  grid->add(current_lqi);
  grid->add(stop);
  grid->set_selected(3, true);
  grid->display();
}