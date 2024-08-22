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

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7735
#include <Arduino.h>

#include <GFXForms.hpp>

#include "SPI.h"
#include "ble_hid/BLEHid.hpp"  // Without this build fails
#include "debug.h"
#include "freertos/task.h"
#include "gui.hpp"
#include "i18n.hpp"
#include "navigation/buttons/btn_routines.hpp"
#include "navigation/navigation.hpp"
#include "pins.h"
#include "posixsd.hpp"
#include "style.h"
#include "display_config.h"

/* TODO: To lower this, we can may switch to heap for wifi_networks */
#define TASK_STACK_SIZE 16000

static void init_sd() {
    SPI.begin(SD_CARD_SCK, SD_CARD_MISO, SD_CARD_MOSI, SD_CARD_CS);
    if (!init_sdcard(SD_CARD_CS)) {
        LOG_ERROR("init_sdcard failed");
    };
}

void init_navigation_btn(int pin, void callback()) {
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(pin, callback, FALLING);
}

Gui *main_gui;
Adafruit_ST7789 *display;
GFXForms *screen;


void setup() {
#ifdef ARDUINO_NANO_ESP32
    Serial.begin(115200);
    Serial.println("Test");
    delay(2000);
#else
    Serial0.begin(115200);
#endif
    init_sd();
    init_english_dict();

    display = new Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
    screen = new GFXForms(DISPLAY_WIDTH, DISPLAY_HEIGHT, display);
    screen->set_rotation(1);
    screen->set_background_color(HOME_BACKGROUND_COLOR);
    main_gui = new Gui(screen);
    main_gui->init_gui();
    init_navigation_btn(UP_BTN_PIN, handle_up_button);
    init_navigation_btn(DOWN_BTN_PIN, handle_down_button);
    init_navigation_btn(RIGHT_BTN_PIN, handle_right_button);
    init_navigation_btn(LEFT_BTN_PIN, handle_left_button);
    init_navigation_btn(OK_BTN_PIN, handle_ok_button);

    xTaskCreate(&set_selected_listener, "set_selected_listener", 8192,
                (void *)main_gui, 1, NULL);
}

void loop() {
    LOG_INFO("Loop\n");  // Avoid FreeRTOS watchdog trigger
    delay(1000);
}
