
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

#include "IRMainPage.hpp"

#include "../../i18n.hpp"
#include "../../navigation/IR/IRNavigation.hpp"
#include "gui.hpp"

IRMainPage::~IRMainPage() {
  delete record_signal;
  delete emulate_signal;
  delete emulate_rc;
  delete go_back;
}

void IRMainPage::display() {
  grid = new Grid(screen, 4, 1);
  record_signal = new List(screen, "Record signal", 2, ST77XX_WHITE, 20,
                           ST77XX_BLACK, goto_ir_record_signal_page);
  emulate_signal = new List(screen, "Emulate signal", 2, ST77XX_WHITE, 20,
                            ST77XX_BLACK, goto_ir_send);
  emulate_rc = new List(screen, "Emulate RC", 2, ST77XX_WHITE, 20, ST77XX_BLACK,
                        goto_ir_rc_browser);
  go_back = new List(screen, "Go back", 2, ST77XX_WHITE, 20, ST77XX_BLACK,
                     ir_goto_home);

  grid->add(record_signal);
  grid->add(emulate_signal);
  grid->add(emulate_rc);
  grid->add(go_back);
  grid->set_selected(0, true);
  grid->display();
}
