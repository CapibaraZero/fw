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

#include "MainPage.hpp"

#include "../../i18n.hpp"
#include "../../include/debug.h"
#include "../../include/device_info.h"
#include "../../include/pins.h"
#include "../../navigation/navigation.hpp"
#include "GFXForms.hpp"
#include "battery_monitor.hpp"
#include "gui.hpp"
#include "i18n/main_page_keys.h"
#include "style.h"

MainPage::~MainPage() {
  // MainPage never get destroyed
}

void section_not_ready() { LOG_ERROR("Section not ready"); }
void MainPage::display() {
  current_position = 0;
  if (wifi == nullptr && SubGhz == nullptr && NFC == nullptr && IR == nullptr &&
      settings == nullptr && grid == nullptr) {
    wifi = new RectText(screen, english_words->at(WIFI_HOME_KEY),
                        HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT,
                        HOME_ICON_RADIUS, HOME_ICON_COLOR, init_wifi_ui);
#ifndef CONFIG_IDF_TARGET_ESP32S2
    ble = new RectText(screen, english_words->at(BLE_HOME_KEY), HOME_TEXT_SIZE,
                       HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS,
                       HOME_ICON_COLOR, init_ble_ui);
#endif
#if defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3)
    badusb = new RectText(screen, english_words->at(BADUSB_HOME_KEY),
                          HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT,
                          HOME_ICON_RADIUS, HOME_ICON_COLOR, init_badusb_ui);
#endif
    SubGhz = new RectText(screen, english_words->at(SUBGHZ_HOME_KEY),
                          HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT,
                          HOME_ICON_RADIUS, HOME_ICON_COLOR, init_subghz_ui);
    NFC = new RectText(screen, english_words->at(NFC_HOME_KEY), HOME_TEXT_SIZE,
                       HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS,
                       HOME_ICON_COLOR, init_nfc_ui);
    IR = new RectText(screen, english_words->at(IR_HOME_KEY), HOME_TEXT_SIZE,
                      HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS,
                      HOME_ICON_COLOR, init_ir_ui);
    scripts = new RectText(screen, "JS", HOME_TEXT_SIZE,
                      HOME_TEXT_COLOR, HOME_ICON_HEIGHT, HOME_ICON_RADIUS,
                      HOME_ICON_COLOR, init_scripts_ui);
    settings =
        new RectText(screen, english_words->at(SETTINGS_HOME_KEY),
                     HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT,
                     HOME_ICON_RADIUS, HOME_ICON_COLOR, init_settings_ui);

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
    grid->add(scripts);
    grid->add(settings);
#if DISPLAY_WIDTH == 170 && DISPLAY_HEIGHT == 320
    btn_level = new Text(screen, HOME_TEXT_COLOR, "100%");
    grid->add(btn_level);
#endif
    grid->set_pos(0, 0);
    grid->set_space_between(10);
    grid->set_padding(0, 10);
  }
#if DISPLAY_WIDTH != 170
  Text battery_level = Text(screen, HOME_INFO_COLOR, "Battery: 0%", 2U, true);
  battery_level.set_pos(5, 220);

  text = new Text(screen, HOME_INFO_COLOR,
                  String(english_words->at(VERSION_KEY)) + String(VERSION));
  text->set_size(2);
  text->set_wrap(true);
  text->set_pos(5, 200);
#endif
  grid->display();
  grid->set_selected(lower_limit, true);
#if DISPLAY_WIDTH != 170
  text->display();
  battery_level.display();
#endif
  set_battery_level();
}

int MainPage::read_bat_level() { return read_battery_level(); }

void MainPage::right() {
  if (current_position >= 0 && current_position < position_limit) {
    grid->set_selected(current_position, false);
    current_position++;
  }
  grid->set_selected(current_position, true);
}

void MainPage::left() {
  if (current_position > 0 && current_position <= position_limit) {
    grid->set_selected(current_position, false);
    current_position--;
  }
  grid->set_selected(current_position, true);
}