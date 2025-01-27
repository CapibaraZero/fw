/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2025 Andrea Canale.
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

#include "../../pages/Settings/SettingsPage.hpp"
#include "gui.hpp"
#include "../navigation.hpp"
#include "../../navigation/SubGHZ/SubGHZNavigation.hpp"

static SettingsPage *settings = nullptr;
static Gui *gui = nullptr;

void goto_back_to_home() {
    init_main_gui();
}

void goto_settings_ui() {
    String subghz_rev = get_subghz_chip_revision();
    size_t pos_limit = SD.cardType() != CARD_NONE ? 12 : 10;
    size_t lower_limit = SD.cardType() != CARD_NONE ? 5 : 3;
    #if !defined(WAKEUP_PIN)
    pos_limit--;
    lower_limit--;
    #endif
    settings = new SettingsPage(pos_limit, lower_limit, 1, gui->get_screen());
    gui->reset();
    settings->display(subghz_rev);
    gui->set_current_page(settings, false);
}

void init_settings_navigation(Gui *_gui) {
    gui = _gui;
}