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
#include "boards/esp32_s3_devkitc/Peripherals_ESP32S3_DevKitC.hpp"

#elif ARDUINO_NANO_ESP32

#include "boards/arduino_nano_esp32/Peripherals_Arduino_Nano_ESP32.hpp"

#elif LILYGO_T_EMBED_CC1101

#include "boards/lilygo_t_embed_cc1101/Peripherals_Lilygo_t_embed_cc1101.hpp"

#endif

#ifndef PERIPHERALS_H
#define PERIPHERALS_H
#include <Arduino.h> 

class Peripherals
{
protected:
    bool common_init_sd(size_t sck, size_t miso, size_t mosi, size_t cs);
    void common_init_navigation(size_t up, size_t down, size_t left,
                                         size_t right, size_t ok);
    void init_navigation_btn(int pin, void callback(), int input_mode=INPUT_PULLUP, int isr_mode=FALLING);

public:
    Peripherals() {};
    ~Peripherals() {};
    virtual void init_i2c_bus() = 0;
    virtual void init_sd() = 0;
    virtual void init_navigation() = 0;
};

#endif