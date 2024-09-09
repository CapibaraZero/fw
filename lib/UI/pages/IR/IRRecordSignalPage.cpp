
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

#include "IRRecordSignalPage.hpp"

#include "../../i18n.hpp"
#include "../../navigation/IR/IRNavigation.hpp"
#include "gui.hpp"

IRRecordSignalPage::~IRRecordSignalPage() {
        Serial.println("Destroy");

}

void IRRecordSignalPage::display() {
  grid = new Grid(screen, 3, 1);
  protocol = new Text(screen, ST77XX_WHITE, "Waiting for signal...");
  stop = new List(screen, "Stop", 2, ST77XX_WHITE, 20, ST77XX_BLACK, goto_ir_gui);

  grid->add(protocol);
  grid->add(stop);
  grid->set_selected(1, true);
  grid->set_y_spacing(30);
  grid->display();
}

void IRRecordSignalPage::set_signal(String _protocol, int _addr, int _cmd, uint32_t _len) {
  grid->set_selected(1, false);
  screen->reset();
  grid->remove(1);  // Remove stop
  if(_addr != -1 && _cmd != -1) {
    addr = new Text(screen, ST77XX_WHITE, "Address: " + _addr);
    cmd = new Text(screen, ST77XX_WHITE, "CMD:" + _cmd);
    grid->add(addr);
    grid->add(cmd);
  }
  Serial.println((String)_len);
  len = new Text(screen, ST77XX_WHITE, "Length: " + (String)_len);
  save = new List(screen, "Save", 2, ST77XX_WHITE, 20, ST77XX_BLUE, save_record_to_sd);
  retry = new List(screen, "Retry", 2, ST77XX_WHITE, 20, ST77XX_BLACK, goto_ir_record_signal_page);
  grid->add(len);
  grid->add(save);
  grid->add(retry);
  grid->add(stop);
  size_t selected_widget = _addr == -1 ? 2 : 4;
  size_t limit = _addr == -1 ? 4 : 6;
  grid->set_selected(selected_widget, true);
  current_position = selected_widget;
  protocol->set_text("Protocol: " + _protocol);
  position_limit = limit;
  lower_limit = selected_widget;
  position_increment = 1;
  grid->display();
}