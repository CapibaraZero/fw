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

#include "buttons.h"

static Buttons btn_pressed = NULL_BTN;

/* ISR routines */
void handle_up_button() {
  btn_pressed = UP_BTN;
}

void handle_down_button() {
  btn_pressed = DOWN_BTN;
}

void handle_left_button() {
  btn_pressed = LEFT_BTN;
}

void handle_right_button() {
  btn_pressed = RIGHT_BTN;
}

void handle_ok_button() {
  btn_pressed = OK_BTN;
}

Buttons get_btn_pressed() {
    return btn_pressed;
}

void reset_btn_state() {
  btn_pressed = NULL_BTN;
}