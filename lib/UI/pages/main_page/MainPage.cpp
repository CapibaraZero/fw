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

#include "MainPage.hpp"

#include "../../i18n.hpp"
#include "../../include/debug.h"
#include "../../include/device_info.h"
#include "../../navigation/navigation.hpp"
#include "GFXForms.hpp"
#include "gui.hpp"
#include "i18n/main_page_keys.h"
#include "style.h"

MainPage::~MainPage() {}

void section_not_ready() { LOG_ERROR("Section not ready"); }
void MainPage::display() {
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
                      HOME_ICON_COLOR, section_not_ready);
    net_attacks = new RectText(screen, english_words->at(NET_ATTACKS_HOME_KEY),
                               HOME_TEXT_SIZE, HOME_TEXT_COLOR,
                               HOME_ICON_HEIGHT, HOME_ICON_RADIUS,
                               HOME_ICON_COLOR, init_network_attacks_ui);
    settings =
        new RectText(screen, english_words->at(SETTINGS_HOME_KEY),
                     HOME_TEXT_SIZE, HOME_TEXT_COLOR, HOME_ICON_HEIGHT,
                     HOME_ICON_RADIUS, HOME_ICON_COLOR, section_not_ready);

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
    // grid->add(settings);
    grid->set_pos(0, 10);
    grid->set_space_between(10);
    grid->set_padding(0, 20);
    Text text = Text(screen, HOME_INFO_COLOR,
                     String(english_words->at(VERSION_KEY)) + String(VERSION) +
                         String(" - ") + String(DEVICE));
    text.set_size(2);
    text.set_wrap(true);
    text.set_pos(5, 200);
    gui->set_current_page(this);
    grid->display();
    grid->set_selected(lower_limit, true);
    text.display();
}

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