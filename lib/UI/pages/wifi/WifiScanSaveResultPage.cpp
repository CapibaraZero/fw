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

#include "WifiScanSaveResultPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/wifi/wifi_scan_keys.h"
#include "../../navigation/wifi/wifi_navigation.hpp"
#include "gui.hpp"

WifiScanSaveResultPage::~WifiScanSaveResultPage() {
  delete save_sd;
  delete sniff_filter;
  delete go_back;
  delete exit_btn;
}

void WifiScanSaveResultPage::up() {
  if (empty) return;
  if (selection_index == 0) return;
  grid->set_selected(selection_index, false);
  selection_index--;
  grid->set_selected(selection_index, true);
}
void WifiScanSaveResultPage::down() {
  if (empty) return;
  if (selection_index == 3) return;
  grid->set_selected(selection_index, false);
  selection_index++;
  grid->set_selected(selection_index, true);
}

void WifiScanSaveResultPage::display(bool _empty) {
  empty = _empty;
  grid = new Grid(screen, 4, 1);
  if (!empty) {
    save_sd = new List(screen, english_words->at(WIFI_SCAN_SAVE_SD_KEY), 2,
                       ST77XX_WHITE, 20, ST77XX_BLACK, save_wifi_scan_to_sd);
    sniff_filter =
        new List(screen, english_words->at(WIFI_SCAN_SNIFF_FILTER_KEY), 2,
                 ST77XX_WHITE, 20, ST77XX_BLACK, sniff_only_bssid);
    go_back = new List(screen, english_words->at(WIFI_SCAN_GO_BACK_KEY), 2,
                       ST77XX_WHITE, 20, ST77XX_BLACK, go_back_to_net_list);
  }
  exit_btn = new List(screen, english_words->at(WIFI_SCAN_EXIT_KEY), 2,
                      ST77XX_WHITE, 20, ST77XX_BLACK, wifi_goto_home);
  if (!empty) {
    grid->add(save_sd);
    grid->add(sniff_filter);
    grid->add(go_back);
  }
  grid->add(exit_btn);
  grid->display();
  grid->set_selected(0, true);
}
