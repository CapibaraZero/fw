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

#include "../Page.hpp"
#include "Grid.hpp"
#include "List.hpp"

#ifndef SUBGHZ_RAW_RECORD_PAGE_H
#define SUBGHZ_RAW_RECORD_PAGE_H

class SubGHZRAWRecordPage : public Page {
   private:
    Text *current_frequency;
    Text *current_rssi;
    Text *current_lqi;
    Text *received_packets;
    List *stop;
    Grid *SubGHZ_grid;

   public:
    SubGHZRAWRecordPage(GFXForms *_screen);
    ~SubGHZRAWRecordPage();
    void display();
    void click(int pos, void callback()) { SubGHZ_grid->click(pos, callback); };
    void set_selected(int pos, bool status) {
        SubGHZ_grid->set_selected(pos, status);
    };
    void set_rssi(int rssi) { current_rssi->set_text("RSSI: " + String(rssi)); }
    void set_lqi(int lqi) { current_lqi->set_text("LQI: " + String(lqi)); }
    void set_frequency(int frequency) {
        current_frequency->set_text("Frequency: " + String(frequency) + "MHz");
    }
    void up() {};
    void down() {};
    void left() {};
    void right() {};
};

#endif