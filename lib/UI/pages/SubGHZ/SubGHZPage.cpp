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

SubGHZPage::SubGHZPage(GFXForms *_screen) { screen = _screen; }

SubGHZPage::~SubGHZPage() {}

void SubGHZPage::display() {
    SubGHZ_grid = new Grid(screen, 4, 1);
    SubGHZ_freq_analyzer = new List(screen, "Frequency analyzer", 2,
                                    ST77XX_WHITE, 20, ST77XX_BLACK);
    SubGHZ_sniff =
        new List(screen, "Record RAW", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
    SubGHZ_sender =
        new List(screen, "Sender", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
    SubGHZ_jammer =
        new List(screen, "Jammer", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
    go_back = new List(screen, "Go back", 2, ST77XX_WHITE, 20, ST77XX_BLACK);
    SubGHZ_grid->add(SubGHZ_freq_analyzer);
    SubGHZ_grid->add(SubGHZ_sniff);
    SubGHZ_grid->add(SubGHZ_sender);
    SubGHZ_grid->add(go_back);
    SubGHZ_grid->set_selected(0, true);
    SubGHZ_grid->display();
}