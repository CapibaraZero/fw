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

#ifndef SUBGHZ_NAVIGATION_H
#define SUBGHZ_NAVIGATION_H

#include "gui.hpp"

void goto_subghz_gui();
void init_subghz_navigation(Gui *_gui);
void stop_frequency_analyzer();
void stop_subghz_raw_record();
void start_subghz_emulation(int pos);
void goto_home_from_subghz();
void subghz_sender_file_browser();
void start_raw_record();
void start_frequency_analyzer();
void set_subghz_freqeuncy(float freq);
void set_subghz_rssi(int rssi);
void set_subghz_raw_record_freq(float freq);
void set_subghz_raw_record_rssi(float rssi);

void set_subghz_sender_freq(float freq);
void set_subghz_sender_bandwidth(float bandwidth);
void set_subghz_sender_deviation(float deviation);
void set_subghz_sender_modulation(int modulation);
String get_subghz_chip_revision();
#endif
