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

// Define buttons pins
#define OK_BTN_PIN 40
#define UP_BTN_PIN 47
#define DOWN_BTN_PIN 41
#define LEFT_BTN_PIN 39
#define RIGHT_BTN_PIN 42

// Display pins
#define TFT_RST 4
#define TFT_DC 5
#define TFT_CS 10
#define TFT_MOSI 11
#define TFT_SCLK 12

// SD card
#define SD_CARD_CS 13
#define SD_CARD_MOSI 35
#define SD_CARD_SCK 36
#define SD_CARD_MISO 37

// CC1101 pins
#define CC1101_CSN 1
#define CC1101_GDO0 2
#define CC1101_MOSI 35
#define CC1101_SCK 36
#define CC1101_MISO 37
#define CC1101_DGO2 RADIOLIB_NC // Not used