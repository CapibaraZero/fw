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

#include "NFCPollingWaitingPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/NFC/nfc_polling_waiting_page.h"
#include "../../navigation/NFC/NFCNavigation.hpp"
#include "gui.hpp"

NFCPollingWaitingPage::~NFCPollingWaitingPage() {
  delete polling_in_progress;
  delete info_msg;
  delete go_back;
}

void NFCPollingWaitingPage::display() {
  grid = new Grid(screen, 2, 1);
  polling_in_progress = new Text(screen, ST77XX_WHITE,
                                 english_words->at(NFC_POLLING_PROGRESS_KEY));
  info_msg = new Text(screen, ST77XX_WHITE, english_words->at(NFC_TAG_NEAR_KEY),
                      2, true);  // Need wrap because text is too long
  go_back = new List(screen, english_words->at(NFC_GO_BACK_KEY), 2,
                     ST77XX_WHITE, 20, ST77XX_BLUE, stop_nfc_polling);
  grid->add(polling_in_progress);
  grid->add(info_msg);
  grid->add(go_back);
  grid->set_y_spacing(40);
  grid->display();
}
