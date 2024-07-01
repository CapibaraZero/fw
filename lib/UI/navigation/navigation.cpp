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

#include "BLE/ble_navigation.hpp"
#include "BadUSB/BadUSBNavigation.hpp"
#include "SubGHZ/SubGHZNavigation.hpp"
#include "NFC/NFCNavigation.hpp"
#include "buttons/btn_routines.hpp"
#include "gui.hpp"
#include "network_attacks/network_attacks_navigation.hpp"
#include "wifi/wifi_navigation.hpp"
#include "../../../include/debug.h"

#define WIFI_MODULE_POS 0
#define BLE_MODULE_POS 1
#define BADUSB_MODULE_POS 2
#define SUBGHZ_MODULE_POS 3
#define NFC_MODULE_POS 4
#define NETWORK_ATTACKS_MODULE_POS 6

static Gui *gui;

void init_main_gui() {
  gui->reset();
  // gui->wifi_cleanup();
  gui->init_gui();
  gui->set_current_position(0);
  gui->set_selected_widget(0, true);
}

void main_menu_handler(int pos) {
#ifdef CONFIG_DEBUG_WIFI_MENU
  LOG_INFO("Submenu1");
#endif
  switch (pos) {
    case WIFI_MODULE_POS:  // Open Wi-Fi submenu
      init_wifi_navigation(gui);
      gui->ok(init_wifi_gui);
      break;
    case BLE_MODULE_POS:
      init_ble_navigation(gui);
      gui->ok(goto_ble_gui);
      break;
    case BADUSB_MODULE_POS:
      init_badusb_navigation(gui);
      gui->ok(goto_badusb_gui);
      break;
    case SUBGHZ_MODULE_POS:
      init_subghz_navigation(gui);
      gui->ok(goto_subghz_gui);
      break;
    case NFC_MODULE_POS:
      init_nfc_navigation(gui);
      gui->ok(goto_nfc_gui);
      break;
    case NETWORK_ATTACKS_MODULE_POS:
      init_network_attacks_navigation(gui);
      gui->ok(goto_net_attacks_gui);
      break;
    default:
#ifdef CONFIG_DEBUG_WIFI_MENU
      LOG_INFO("Not implemented");
#endif
      break;
  }
  return;
}

static void handle_ok() {
  int pos = gui->get_current_position();
  /* Main menu handler */
  if (!gui->submenu_visible()) {
    main_menu_handler(pos);
    return;
  }
Serial.println("WiFI1");
  /* Wi-Fi submenu handler */
  if (gui->get_wifi_sub_menu()) {
    wifi_submenu_handler(pos);
    return;
  }
Serial.println("WiFI2");

  if (gui->get_wifi_sniff_menu()) {
    stop_wifi_sniffer();
    return;
  }
Serial.println("WiFI3");

  if (gui->wifi_scan_save_visible()) {
    handle_wifi_network_selection();
    return;
  }
Serial.println("WiFI4");

  if (gui->get_wifi_scan_result_visible()) {
    display_wifi_scan_result();
    return;
  }

  if (gui->get_ble_sub_menu()) {
    ble_submenu_handler(pos);
    return;
  }

  if (gui->ble_sniff_visible()) {
    stop_ble_sniffer();
    return;
  }

  if (gui->ble_spam_visible()) {
    handle_ble_spam_stop();
    return;
  }

  if (gui->badusb_browser_visible()) {
    badusb_selection_handler(pos);
    return;
  }

  if(gui->subghz_page_visible()) {
    Serial.println("SUBGHZ PAGE");
    subghz_submenu_handler(pos);
    return;
  }

  if(gui->subghz_frequency_analyzer_visible()) {
    Serial.println("PAGE ANALZYER");
    stop_frequency_analyzer();
    return;
  }  

  if(gui->subghz_raw_record_ui_visible()) {
    Serial.println("PAGE RAW RECORD");
    stop_subghz_raw_record();
    return;
  }

  if(gui->subghz_sender_visible()) {
    // SubGHZ sender haven't any button
    return;
  }

  if(gui->subghz_file_browser_visible()) {
    Serial.println("PAGE FILE BROWSER");
    start_subghz_emulation(pos);
    // stop_subghz_file_browser();
    return;
  }

  if (gui->network_attacks_submenu_visible()) {
    network_attacks_submenu_handler(pos);
    return;
  }

  if (gui->dhcp_glutton_visible()) {
    stop_dhcpglutton();
    return;
  }

  if (gui->evilportal_page_visible()) {
    stop_evilportal();
    return;
  }

  if(gui->arp_poisoner_page_visible()){
    stop_arp_poisoner();
    return;
  }

  if (gui->nfc_page_visible()) {
    nfc_submenu_handler(pos);
    return;
  }

  if (gui->nfc_polling_waiting_page_visible()) {
    stop_nfc_polling();
    return;
  }

  if (gui->nfc_format_page_visible()) {
    nfc_format_submenu_handler(pos);
    return;
  }

  if (gui->nfc_dump_result_page_visible()) {
    nfc_dump_submenu_handler(pos);
    return;
  }

  if (gui->nfc_bruteforce_page_visible()) {
    // LOG_INFO("nfc_bruteforce_page_visible");
    nfc_bruteforce_submenu_handler(pos);
    return;
  }

  if (gui->nfc_polling_result_page_visible()) {
    nfc_polling_submenu_handler(pos);
    return;
  }

  if (gui->nfc_felica_polling_result_page_visible()) {
    nfc_felica_polling_submenu_handler(pos);
    return;
  }
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

    if (get_btn_pressed() == OK_BTN) handle_ok();

    if (get_btn_pressed() != -1) reset_btn_state();  // Reset button status
  }
}
