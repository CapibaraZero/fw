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

#include "buttons/btn_routines.hpp"
#include "gui.hpp"
#include "wifi/wifi_navigation.hpp"

static Gui *gui;

void init_main_gui() {
  gui->reset();
  gui->wifi_cleanup();
  gui->init_gui();
  gui->set_selected_widget(0, true);
}

static void handle_ok() {
  int pos = gui->get_current_position();
  Serial0.println(pos);
  /* Main menu handler */
  if (!gui->submenu_visible()) {
    main_menu_handler(pos);
    return;
  }

  /* Wi-Fi submenu handler */
  if (gui->get_wifi_sub_menu()) {
    wifi_submenu_handler(pos);
    return;
  }

  if (gui->get_wifi_sniff_menu()) {
    stop_wifi_sniffer();
    return;
  }

  if (gui->wifi_scan_save_visible()) {
    Serial0.println("Selection is visible");
    handle_wifi_network_selection();
    return;
  }

  if (gui->get_wifi_scan_result_visible()) {
    gui->show_wifi_scan_result_dialog();
    return;
  }
}

/*
  ISR routines should be short, since display is slow,
  we use a task to control display element selection
*/
void set_selected_listener(void *pv) {
  gui = static_cast<Gui *>(pv);
  init_wifi_navigation(gui);
  while (true) {
    if (get_btn_pressed() == -1) {
      vTaskDelay(1 / portTICK_PERIOD_MS);  // Avoid wdt trigger
      continue;
    }

    if (get_btn_pressed() == UP_BTN)
      gui->up();

    if (get_btn_pressed() == DOWN_BTN)
      gui->down();

    if (get_btn_pressed() == LEFT_BTN) {
      gui->left();
    }

    if (get_btn_pressed() == RIGHT_BTN)
      gui->right();

    if (get_btn_pressed() == OK_BTN)
      handle_ok();

    if (get_btn_pressed() != -1)
      reset_btn_state();  // Reset button status
  }
}
