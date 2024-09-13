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

#include "BLESpamPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/BLE/ble_spam_keys.h"
#include "../../navigation/BLE/ble_navigation.hpp"
#include "gui.hpp"

BLESpamPage::~BLESpamPage() {
  delete text;
  delete save;
}

void BLESpamPage::display() {
  text =
      new Text(screen, ST77XX_WHITE, english_words->at(BLE_SPAM_PROGRESS_KEY));
  grid = new Grid(screen, 2, 1);
  save = new List(screen, english_words->at(BLE_SPAM_STOP_KEY), 2, ST77XX_WHITE,
                  20, ST77XX_BLACK, handle_ble_spam_stop);
  grid->add(text);
  grid->add(save);
  grid->set_selected(1, true);
  grid->set_y_spacing(20);
  grid->display();
}