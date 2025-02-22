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

#include "SubGHZPage.hpp"

#include "../../i18n.hpp"
#include "../../navigation/SubGHZ/SubGHZNavigation.hpp"
#include "gui.hpp"

SubGHZPage::~SubGHZPage() {
  delete SubGHZ_freq_analyzer;
  delete SubGHZ_sniff;
  delete SubGHZ_sender;
  delete go_back;
}

void SubGHZPage::display() {
  grid = new Grid(screen, 4, 1);
  SubGHZ_freq_analyzer = new List(screen, "Frequency analyzer", 2, ST77XX_WHITE,
                                  20, ST77XX_BLACK, start_frequency_analyzer);
  SubGHZ_sniff = new List(screen, "Record RAW", 2, ST77XX_WHITE, 20,
                          ST77XX_BLACK, start_raw_record);
  SubGHZ_sender = new List(screen, "Sender", 2, ST77XX_WHITE, 20, ST77XX_BLACK,
                           subghz_sender_file_browser);
  // SubGHZ_jammer =
  //     new List(screen, "Jammer", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  go_back = new List(screen, "Go back", 2, ST77XX_WHITE, 20, ST77XX_BLACK,
                     goto_home_from_subghz);
  grid->add(SubGHZ_freq_analyzer);
  grid->add(SubGHZ_sniff);
  grid->add(SubGHZ_sender);
  grid->add(go_back);
  grid->set_selected(0, true);
  grid->display();
}