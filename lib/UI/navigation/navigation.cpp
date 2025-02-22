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

#include "../../../include/debug.h"
#include "BLE/ble_navigation.hpp"
#include "BadUSB/BadUSBNavigation.hpp"
#include "IR/IRNavigation.hpp"
#include "NFC/NFCNavigation.hpp"
#include "SubGHZ/SubGHZNavigation.hpp"
#include "buttons/btn_routines.hpp"
#include "gui.hpp"
#include "Settings/SettingsNavigation.hpp"
#include "scripts/ScriptsNavigation.hpp"
#include "wifi/wifi_navigation.hpp"

static Gui *gui;

void init_main_gui() {
  gui->reset();
  gui->init_gui();
}

void init_wifi_ui() {
  init_wifi_navigation(gui);
  init_wifi_gui();
}

void init_ble_ui() {
  init_ble_navigation(gui);
  goto_ble_gui();
}

void init_badusb_ui() {
  init_badusb_navigation(gui);
  goto_badusb_gui();
}

void init_subghz_ui() {
  init_subghz_navigation(gui);
  goto_subghz_gui();
}

void init_nfc_ui() {
  init_nfc_navigation(gui);
  goto_nfc_gui();
}

void init_ir_ui() {
  init_ir_navigation(gui);
  goto_ir_gui();
}

void init_settings_ui() {
  init_settings_navigation(gui);
  goto_settings_ui();
}

void init_scripts_ui() {
  init_scripts_navigation(gui);
  goto_scripts_ui();
}

/*
  ISR routines should be short, since display is slow,
  we use a task to control display element selection
*/
void set_selected_listener(void *pv) {
  gui = static_cast<Gui *>(pv);

  while (true) {
    if (get_btn_pressed() == -1) {
      vTaskDelay(1 / portTICK_PERIOD_MS);  // Avoid wdt trigger
      continue;
    }

    if (get_btn_pressed() == UP_BTN) gui->up();

    if (get_btn_pressed() == DOWN_BTN) gui->down();

    if (get_btn_pressed() == LEFT_BTN) {
      gui->left();
    }

    if (get_btn_pressed() == RIGHT_BTN) gui->right();

    if (get_btn_pressed() == OK_BTN) gui->click_element();

    if (get_btn_pressed() != -1) reset_btn_state();  // Reset button status
  }
}
