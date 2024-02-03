/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or https://capibarazero.github.io/).
 * Copyright (c) 2024 Andrea Canale.
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

#include "BLESpamPage.hpp"
#include "../../i18n.hpp"
#include "../../i18n/BLE/ble_spam_keys.h"

BLESpamPage::BLESpamPage(GFXForms *_screen) {
  text = new Text(_screen, ST77XX_WHITE, english_words->at(BLE_SPAM_PROGRESS_KEY));
  details_grid = new Grid(_screen, 2, 1);
  save = new List(_screen, english_words->at(BLE_SPAM_STOP_KEY), 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  details_grid->add(text);
  details_grid->add(save);
  details_grid->set_selected(1, true);
  details_grid->set_y_spacing(20);
}

BLESpamPage::~BLESpamPage() {
}
