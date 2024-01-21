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

#include "gui.hpp"

#include "../../include/device_info.h"
#include "GFXForms.hpp"
#include "i18n.hpp"
#include "i18n/main_page_keys.h"
#include "style.h"

void Gui::init_icons() {
  wifi = new RectText(screen, english_words->at(WIFI_HOME_KEY), HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS, HOME_ICON_COLOR);
#ifndef CONFIG_IDF_TARGET_ESP32S2
  ble = new RectText(screen, english_words->at(BLE_HOME_KEY), HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS, HOME_ICON_COLOR);
#endif
#if defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3)
  badusb = new RectText(screen, english_words->at(BADUSB_HOME_KEY), HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS, HOME_ICON_COLOR);
#endif
  SubGhz = new RectText(screen, english_words->at(SUBGHZ_HOME_KEY), HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS, HOME_ICON_COLOR);
  NFC = new RectText(screen, english_words->at(NFC_HOME_KEY), HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS, HOME_ICON_COLOR);
  IR = new RectText(screen, english_words->at(IR_HOME_KEY), HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS, HOME_ICON_COLOR);
  net_attacks = new RectText(screen, english_words->at(NET_ATTACKS_HOME_KEY), HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS, HOME_ICON_COLOR);
  settings = new RectText(screen, english_words->at(SETTINGS_HOME_KEY), HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS, HOME_ICON_COLOR);

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
  Text text = Text(screen, HOME_INFO_COLOR, String(english_words->at(VERSION_KEY)) + String(VERSION) + String(" - ") + String(DEVICE));
  text.set_size(2);
  text.set_wrap(true);
  text.set_pos(5, 200);
  text.display();
}

void Gui::init_gui() {
  // current_position = 0;
  init_icons();
  init_text();
}

void Gui::init_wifi_gui() {
  delete grid;  // Free some spaces
  grid = nullptr;
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
  if (wifi_networks_page == nullptr) /* We can use this page again, so no need to recreate a new one */
    wifi_networks_page = new WifiNetworksPage(screen, networks);
  wifi_networks_page->display();
}

void Gui::set_selected_widget(int pos, bool selected) {
  if (grid != nullptr) {
    grid->set_selected(pos, selected);
  } else if (wifi_page != nullptr) {
    wifi_page->set_selected(pos, selected);
  }
}

void Gui::click_element(int pos, void callback()) {
  if (grid != nullptr)
    grid->click(pos, callback);
  else if (wifi_page != nullptr)
    wifi_page->click(pos, callback);
}
void Gui::up_submenu() {
  int tmp_current_position = current_position - 1;
  if (tmp_current_position >= 0) {
    set_selected_widget(current_position, false);
    current_position = tmp_current_position;
  }
  set_selected_widget(current_position, true);
}

void Gui::down_submenu() {
  int tmp_current_position = current_position + 1;
  if (tmp_current_position <= 1) {
    set_selected_widget(current_position, false);
    current_position = tmp_current_position;
  }
  set_selected_widget(current_position, true);
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
  if (wifi_page != nullptr) {
    up_submenu();
    return;
  }
  int tmp_current_position = current_position - 4;
  if (tmp_current_position >= 0) {
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
  if (wifi_page != nullptr) {
    down_submenu();
    return;
  }
  int tmp_current_position = current_position + 4;
  if (tmp_current_position <= 7) {
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
  if (wifi_page != nullptr) {
    // left_submenu();
    return;
  }
  if (current_position > 0 && current_position <= 7) {
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
  if (wifi_page != nullptr) {
    // right_submenu();
    return;
  }
  if (current_position >= 0 && current_position < 7) {
    set_selected_widget(current_position, false);
    current_position++;
  }
  set_selected_widget(current_position, true);
}

void Gui::ok_submenu(void callback()) {
  click_element(current_position, callback);
}

void Gui::ok(void callback()) {
  if (wifi_page != nullptr) {
    ok_submenu(callback);
    return;
  }
  click_element(current_position, callback);
}

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
