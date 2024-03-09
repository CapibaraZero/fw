
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

#include "BadUSBPayloadBrowserPage.hpp"

#include "../../i18n.hpp"
#include "../../i18n/BadUSB/badusb_keys.h"
#include "Bitmap.hpp"
#include "../../../../include/icons/file/file.h"
BadUSBPayloadBrowserPage::BadUSBPayloadBrowserPage(GFXForms *_screen) {
  screen = _screen;
}

BadUSBPayloadBrowserPage::~BadUSBPayloadBrowserPage() {
}

void BadUSBPayloadBrowserPage::display() {
  badusb_grid = new Grid(screen, 2, 1);
  title = new Text(screen, ST77XX_WHITE, "Bad USB Payload Browser");
  Bitmap bitmap = Bitmap(screen, (uint8_t *)file_icon, 16, 16, 100, 100);
  List file = List(screen, "example", 2, ST77XX_WHITE, 20, &bitmap, ST77XX_BLACK);
  badusb_grid->add(title);
  badusb_grid->add(&file);
  badusb_grid->set_y_spacing(20);
  badusb_grid->display();
}

void BadUSBPayloadBrowserPage::display(std::list<std::string> *files) {
  badusb_grid = new Grid(screen, 2, 1);
  title = new Text(screen, ST77XX_WHITE, english_words->at(BADUSB_TITLE_KEY));
  badusb_grid->add(title);
  Bitmap bitmap = Bitmap(screen, (uint8_t *)file_icon, 16, 16, 100, 100);
  List *file_list = nullptr;  // In for loop, variable got deleted
  for (auto file : *files) {
    file_list = new List(screen, file.c_str(), 2, ST77XX_WHITE, 20, &bitmap, ST77XX_BLACK);
    badusb_grid->add(file_list);
  }
  go_back = new List(screen, english_words->at(BADUSB_GO_BACK_KEY), 2, ST77XX_WHITE, 20, ST77XX_BLACK);
  badusb_grid->add(go_back);
  badusb_grid->set_selected(1, true);
  badusb_grid->set_y_spacing(20);
  badusb_grid->display();
}