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

#ifndef BTN_ROUTINES_H
#define BTN_ROUTINES_H

#include "../../../../include/pins.h"
#include "buttons.h"

#if BTN_NAVIGATION
void handle_up_button();
void handle_down_button();
void handle_left_button();
void handle_right_button();

#elif ENCODER_NAVIGATION
void init_rotary_encoder();
void handle_encoder();
#endif

void handle_ok_button();
Buttons get_btn_pressed();
void reset_btn_state();

#endif