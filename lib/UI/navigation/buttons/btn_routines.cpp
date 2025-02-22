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

#include "../../../../include/pins.h"
#include "buttons.h"

static Buttons btn_pressed = NULL_BTN;

#ifdef BTN_NAVIGATION
/* ISR routines */
void handle_up_button() { btn_pressed = UP_BTN; }

void handle_down_button() { btn_pressed = DOWN_BTN; }

void handle_left_button() { btn_pressed = LEFT_BTN; }

void handle_right_button() { btn_pressed = RIGHT_BTN; }

#elif defined(ENCODER_NAVIGATION)
#include <RotaryEncoder.h>

static RotaryEncoder *encoder = nullptr;

void init_rotary_encoder() {
  encoder = new RotaryEncoder(ENCODER_A_PIN, ENCODER_B_PIN,
                              RotaryEncoder::LatchMode::TWO03);
}

static int pos = 0;
void handle_encoder() {
  encoder->tick();

  int new_pos = encoder->getPosition();
  if (pos != new_pos) {
    pos = new_pos;
    RotaryEncoder::Direction direction = encoder->getDirection();
    if (direction == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
      btn_pressed = RIGHT_BTN;
    } else {
      btn_pressed = LEFT_BTN;
    }
  }
  delay(1);
}
#endif

void IRAM_ATTR handle_ok_button() { 
    btn_pressed = OK_BTN;
}

Buttons get_btn_pressed() { return btn_pressed; }

void reset_btn_state() { btn_pressed = NULL_BTN; }