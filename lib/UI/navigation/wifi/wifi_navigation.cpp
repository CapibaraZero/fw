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

#include <Arduino.h>

#include "../navigation.hpp"
#include "gui.hpp"
#include "wifi_attacks_btn.hpp"
#include "wifi_position.h"
#include "wifi_tasks.hpp"
#include "../../../../include/debug.h"

static Gui *gui;
static WifiAttack wifiAttack = WifiAttack();

static void goto_scan_wifi() { scan_wifi(gui, &wifiAttack); }

static void goto_sniff_wifi() { sniff_wifi(gui, &wifiAttack); }

void init_wifi_gui() {
  gui->reset();
  gui->init_wifi_gui();
}

static void wifi_goto_home() {
  gui->wifi_cleanup();
  init_main_gui();
}

void wifi_submenu_handler(int pos) {
#ifdef CONFIG_DEBUG_WIFI_MENU
  LOG_INFO("Sub menu2");
#endif
  switch (pos) {
    case WIFI_SCAN_POS:  // Start scan
      gui->ok(goto_scan_wifi);
      break;
    case WIFI_SNIFF_POS:  // Start sniff
      gui->ok(goto_sniff_wifi);
      break;
    case WIFI_GO_BACK_POS:
      gui->ok(wifi_goto_home);
      break;
    default:
#ifdef CONFIG_DEBUG_WIFI_MENU
      LOG_INFO("Not implemented");
#endif
      break;
  }
}

void stop_wifi_sniffer() {
#ifdef CONFIG_DEBUG_WIFI_MENU
  LOG_INFO("Sniff menu");
#endif
  /* Stop sniffer */
  wifiAttack.stop_sniff();
  stop_wifi_sniffer_updater();  // Delete updater task to avoid UI crash
  wifiAttack.clean_networks();
  gui->wifi_cleanup();
  init_main_gui();
}

void handle_wifi_network_selection() {
  if (gui->get_selection_index() == WIFI_SCAN_SAVE_TO_SD_POS) {
    // Save to SD
    wifiAttack.save_scan();  // TODO: Create a task for this to create better UX
    wifiAttack.clean_networks();  // Clean previous scan
    gui->wifi_cleanup();  // Remove WiFi pages
    init_main_gui();
  } else if (gui->get_selection_index() == WIFI_SCAN_SNIFF_BSSID_POS) {
    // Sniff only selected BSSID
    sniff_bssid(gui, &wifiAttack);
  } else if (gui->get_selection_index() == WIFI_SCAN_GO_BACK_POS) {
    return_to_net_list(gui);  // Go back to network selection
  } else {
    gui->wifi_cleanup();
    // Go to main menu
    init_main_gui();
  }
}

void init_wifi_navigation(Gui *_gui) { gui = _gui; }
