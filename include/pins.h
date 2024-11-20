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

#ifdef ESP32S3_DEVKITC_BOARD

#include "boards/esp32_s3_devkitc/pins.h"

#elif ARDUINO_NANO_ESP32

#include "boards/arduino_nano_esp32/pins.h"

#elif LILYGO_T_EMBED_CC1101

#include "boards/lilygo_t_embed_cc1101/pins.h"

#endif
