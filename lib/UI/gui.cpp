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

#include "gui.hpp"

#include <list>

#include "../../include/device_info.h"
#include "GFXForms.hpp"
#include "i18n.hpp"
#include "i18n/main_page_keys.h"
#include "style.h"

void Gui::init_icons() {
  wifi = new RectText(screen, english_words->at(WIFI_HOME_KEY), HOME_TEXT_SIZE,
                      HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS,
                      HOME_ICON_COLOR);
#ifndef CONFIG_IDF_TARGET_ESP32S2
  ble = new RectText(screen, english_words->at(BLE_HOME_KEY), HOME_TEXT_SIZE,
                     HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS,
                     HOME_ICON_COLOR);
#endif
#if defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3)
  badusb = new RectText(screen, english_words->at(BADUSB_HOME_KEY),
                        HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT,
                        HOME_ICON_RADIUS, HOME_ICON_COLOR);
#endif
  SubGhz = new RectText(screen, english_words->at(SUBGHZ_HOME_KEY),
                        HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT,
                        HOME_ICON_RADIUS, HOME_ICON_COLOR);
  NFC = new RectText(screen, english_words->at(NFC_HOME_KEY), HOME_TEXT_SIZE,
                     HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS,
                     HOME_ICON_COLOR);
  IR = new RectText(screen, english_words->at(IR_HOME_KEY), HOME_TEXT_SIZE,
                    HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS,
                    HOME_ICON_COLOR);
  net_attacks = new RectText(screen, english_words->at(NET_ATTACKS_HOME_KEY),
                             HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT,
                             HOME_ICON_RADIUS, HOME_ICON_COLOR);
  settings = new RectText(screen, english_words->at(SETTINGS_HOME_KEY),
                          HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT,
                          HOME_ICON_RADIUS, HOME_ICON_COLOR);

  grid = new Grid(screen, 2, 4);

  grid->add(wifi);
#ifndef CONFIG_IDF_TARGET_ESP32S2
  grid->add(ble);
#endif
#if defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3)
  grid->add(badusb);
#endif
  grid->add(SubGhz);
  grid->add(NFC);
  grid->add(IR);
  grid->add(net_attacks);
  grid->add(settings);
  grid->set_pos(0, 10);
  grid->set_space_between(10);
  grid->set_padding(0, 20);
  grid->display();
}

void Gui::init_text() {
  Text text = Text(screen, HOME_INFO_COLOR,
                   String(english_words->at(VERSION_KEY)) + String(VERSION) +
                       String(" - ") + String(DEVICE));
  text.set_size(2);
  text.set_wrap(true);
  text.set_pos(5, 200);
  text.display();
}

void Gui::init_gui() {
  position_increment = 4;
  lower_limit = 0;
  position_limit = 7;
  if(grid == nullptr) {
    Serial.println("Allocating grid");
    init_icons();
    init_text();
  } else {
    grid->display();
    init_text();
  }
  grid_visible = true;
}

void Gui::init_wifi_gui() {
  grid_visible = false;
  position_limit = 2;
  position_increment = 1;
  wifi_page = new WifiPage(screen);
  wifi_page->display();
}

void Gui::init_wifi_scan_gui() {
  delete wifi_page;  // Free some spaces
  wifi_page = nullptr;
  wifi_scan_page = new WifiScanPage(screen);
  wifi_scan_page->display();
}

void Gui::init_wifi_networks_gui(vector<WifiNetwork> *networks) {
  delete wifi_scan_page;
  wifi_scan_page = nullptr;
  if (wifi_networks_page == nullptr) /* We can use this page again, so no need
                                        to recreate a new one */
    wifi_networks_page = new WifiNetworksPage(screen, networks);
  wifi_networks_page->display();
}

/*********************** BLE GUI FUNCTIONS *************************/

void Gui::init_ble_gui() {
  grid_visible = false;
  position_limit = 4;
  position_increment = 1;
  ble_page = new BLEPage(screen);
  ble_page->display();
}

void Gui::init_ble_scan_gui() {
  delete ble_page;
  ble_page = nullptr;
  ble_scan_page = new BLEScanPage(screen);
  ble_scan_page->display();
}

void Gui::init_ble_sniff_gui() {
  delete ble_page;
  ble_page = nullptr;
  ble_sniff_page = new BLESniffPage(screen);
  ble_sniff_page->display();
}

void Gui::init_ble_spam_gui() {
  delete ble_page;
  ble_page = nullptr;
  ble_spam_page = new BLESpamPage(screen);
  ble_spam_page->display();
}

/****************** NET ATTACKS GUI FUNCTIONS *********************/

void Gui::init_network_attacks_gui() {
  grid_visible = false;
  position_limit = 3;
  position_increment = 1;
  net_attacks_page = new NetworkAttacksPage(screen);
  net_attacks_page->display();
}

void Gui::init_dhcp_glutton_gui() {
  delete net_attacks_page;
  net_attacks_page = nullptr;
  position_limit = 0;  // It has just one button, so it cannot be increased
  position_increment = 0;
  dhcp_glutton_page = new DHCPGluttonPage(screen);
  dhcp_glutton_page->display();
}

void Gui::set_dhcp_glutton_clients(int client) {
  dhcp_glutton_page->update_packet_count(client);
}

/****************** EVILPORTAL GUI FUNCTIONS *********************/

void Gui::init_evilportal_gui() {
  delete net_attacks_page;
  net_attacks_page = nullptr;
  position_limit = 0;  // It has just one button, so it cannot be increased
  position_increment = 0;
  evilportal_page = new EvilPortalPage(screen);
  evilportal_page->display();
}

void Gui::set_evilportal_requests(int req) {
  evilportal_page->update_requests_count(req);
}

void Gui::set_evilportal_ip(String ip) { evilportal_page->set_portal_ip(ip); }

void Gui::init_arp_poisoner_gui() {
  delete net_attacks_page;
  net_attacks_page = nullptr;
  grid_visible = false;
  position_limit = 0;  // It has just one button, so it cannot be increased
  position_increment = 0;
  arpoisoner_page = new ARPoisonerPage(screen);
  arpoisoner_page->display();
}
void Gui::set_selected_widget(int pos, bool selected) {
  if (grid_visible)
    grid->set_selected(pos, selected);
  else if (wifi_page != nullptr)
    wifi_page->set_selected(pos, selected);
  else if (ble_page != nullptr)
    ble_page->set_selected(pos, selected);
  else if (network_attacks_submenu_visible())
    net_attacks_page->set_selected(pos, selected);
  else if (nfc_page_visible())
    nfc_main_page->set_selected(pos, selected);
  else if (nfc_dump_result_page_visible())
    nfc_dump_result_page->set_selected(pos, selected);
  else if (nfc_format_page_visible())
    nfc_format_result_page->set_selected(pos, selected);
  else if (nfc_polling_result_page_visible())
    nfc_polling_result_page->set_selected(pos, selected);
  else if (nfc_felica_polling_result_page_visible())
    nfc_felica_polling_result_page->set_selected(pos, selected);
  else if (badusb_browser_visible())
    badusb_payload_browser_page->set_selected(pos, selected);
}

/******************** NFC GUI FUNCTIONS ************************/
void Gui::init_nfc_gui() {
  grid_visible = false;
  position_limit = 2;
  position_increment = 1;
  nfc_main_page = new NFCMainPage(screen);
  nfc_main_page->display();
};

void Gui::init_nfc_polling_waiting_gui() {
  delete nfc_main_page;
  nfc_main_page = nullptr;
  position_limit = 0;
  position_increment = 0;
  nfc_polling_waiting_page = new NFCPollingWaitingPage(screen);
  nfc_polling_waiting_page->display();
}

void Gui::init_nfc_polling_result_gui(uint8_t *uid, uint8_t length) {
  delete nfc_polling_waiting_page;
  nfc_polling_waiting_page = nullptr;
  position_limit = 5;
  // position_limit = 4;
  lower_limit = 2;
  position_increment = 1;
  nfc_polling_result_page = new NFCPollingResultPage(screen);
  nfc_polling_result_page->display(uid, length);
}

void Gui::init_nfc_dump_result_gui() {
  // We don't destroy previous page since we may need it again
  // position_limit = 5;
  lower_limit = 4;
  position_limit = 5;
  position_increment = 0;
  nfc_dump_result_page = new NFCDumpResultPage(screen);
  nfc_dump_result_page->display();
}

void Gui::return_to_nfc_polling_gui() {
  position_limit = 5;
  lower_limit = 2;
  position_increment = 1;
  nfc_polling_result_page->display();
}

void Gui::init_nfc_write_result_gui() {
  // We don't destroy previous page since we may need it again
  position_limit = 4;
  lower_limit = 3;
  position_increment = 1;
  nfc_write_result_page = new NFCWriteResultPage(screen);
  nfc_write_result_page->display();
}

void Gui::init_nfc_format_result_gui() {
  // We don't destroy previous page since we may need it again
  // position_limit = 4;
  // lower_limit = 3;
  position_limit = 0;
  position_increment = 0;
  nfc_format_result_page = new NFCFormatResultPage(screen);
  nfc_format_result_page->display();
}

void Gui::init_nfc_bruteforce_gui() {
  // We don't destroy previous page since we may need it again
  // position_limit = 4;
  // lower_limit = 3;
  position_limit = 0;
  position_increment = 0;
  nfc_bruteforce_tag_page = new NFCBruteforceTagPage(screen);
  nfc_bruteforce_tag_page->display();
}

void Gui::init_nfc_felica_polling_result_gui(uint8_t *idm, uint8_t *pmm,
                                             uint16_t sys_code) {
  delete nfc_polling_waiting_page;
  nfc_polling_waiting_page = nullptr;
  lower_limit = 4;
  position_limit = 5;
  position_increment = 1;
  nfc_felica_polling_result_page = new NFCFelicaPollingResultPage(screen);
  nfc_felica_polling_result_page->display(idm, pmm, sys_code);
}
void Gui::nfc_cleanup() {
  delete nfc_polling_result_page;
  nfc_polling_result_page = nullptr;
  delete nfc_dump_result_page;
  nfc_dump_result_page = nullptr;
  delete nfc_write_result_page;
  nfc_write_result_page = nullptr;
  delete nfc_format_result_page;
  nfc_format_result_page = nullptr;
  delete nfc_bruteforce_tag_page;
  nfc_bruteforce_tag_page = nullptr;
}

/******************** BadUSB FUNCTIONS ************************/
void Gui::init_badusb_browser_gui(std::list<std::string> *files) {
  grid_visible = false;
  lower_limit = 1;
  position_limit = 2;  // To adjust dynamically
  position_increment = 1;
  badusb_payload_browser_page = new BadUSBPayloadBrowserPage(screen);
  badusb_payload_browser_page->display(files);
};

void Gui::click_element(int pos, void callback()) {
  if (grid_visible)
    grid->click(pos, callback);
  else if (wifi_page != nullptr)
    wifi_page->click(pos, callback);
  else if (ble_page != nullptr)
    ble_page->click(pos, callback);
  else if (nfc_page_visible())
    nfc_main_page->click(pos, callback);
  else if (nfc_dump_result_page_visible())
    nfc_dump_result_page->click(pos, callback);
  else if (nfc_format_page_visible())
    nfc_format_result_page->click(pos, callback);
  else if (nfc_polling_result_page_visible())
    nfc_polling_result_page->click(pos, callback);
  else if (nfc_felica_polling_result_page_visible())
    nfc_felica_polling_result_page->click(pos, callback);
  else if (badusb_browser_visible())
    badusb_payload_browser_page->click(pos, callback);
}

void Gui::up() {
  if (wifi_save_result_page != nullptr) {
    wifi_save_result_page->up();
    return;
  }
  if (wifi_sniff_page != nullptr) {
    wifi_sniff_page->up();
    return;
  }
  int tmp_current_position = current_position - position_increment;
  if (tmp_current_position >= lower_limit) {
    set_selected_widget(current_position, false);
    current_position = tmp_current_position;
  }
  set_selected_widget(current_position, true);
}

void Gui::down() {
  if (wifi_save_result_page != nullptr) {
    wifi_save_result_page->down();
    return;
  }
  if (wifi_sniff_page != nullptr) {
    wifi_sniff_page->down();
    return;
  }
  int tmp_current_position = current_position + position_increment;
  if (tmp_current_position <= position_limit) {
    set_selected_widget(current_position, false);
    current_position = tmp_current_position;
  }
  set_selected_widget(current_position, true);
}

void Gui::left() {
  if (wifi_sniff_page != nullptr) {
    return;
  }
  if (wifi_networks_page != nullptr) {
    wifi_networks_page->left();
    return;
  }
  if (wifi_page != nullptr || ble_page != nullptr) {
    return;
  }
  if (current_position > 0 && current_position <= position_limit) {
    set_selected_widget(current_position, false);
    current_position--;
  }
  set_selected_widget(current_position, true);
}

void Gui::right() {
  if (wifi_sniff_page != nullptr) {
    return;
  }
  if (wifi_networks_page != nullptr) {
    wifi_networks_page->right();
    return;
  }
  if (wifi_page != nullptr || ble_page != nullptr) {
    return;
  }
  if (current_position >= 0 && current_position < 7) {
    set_selected_widget(current_position, false);
    current_position++;
  }
  set_selected_widget(current_position, true);
}

void Gui::ok(void callback()) { click_element(current_position, callback); }

void Gui::show_wifi_sniff_page() {
  delete wifi_page;
  wifi_page = nullptr;
  wifi_sniff_page = new WifiSniffPage(screen);
  wifi_sniff_page->display();
}

void Gui::show_wifi_scan_result_dialog() {
  if (wifi_networks_page != nullptr) {
    screen->reset();
    wifi_save_result_page = new WifiScanSaveResultPage(screen);
    wifi_save_result_page->display();
    return;
  }
}
void Gui::wifi_cleanup() {
  current_position = 0;
  if(wifi_page != nullptr) {
    delete wifi_page;
    wifi_page = nullptr;
  }

  if(wifi_scan_page != nullptr) {
    delete wifi_scan_page;
    wifi_scan_page = nullptr;
  }
  
  if (wifi_networks_page != nullptr) {
    delete wifi_networks_page;
    wifi_networks_page = nullptr;
  }

  if (wifi_save_result_page != nullptr) {
    delete wifi_save_result_page;
    wifi_save_result_page = nullptr;
  }

  if (wifi_sniff_page != nullptr) {
    delete wifi_sniff_page;
    wifi_sniff_page = nullptr;
  }
}
