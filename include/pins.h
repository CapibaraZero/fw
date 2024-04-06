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

#define PN532_SDA 8
#define PN532_SCL 9

#elif ARDUINO_NANO_ESP32

// Define buttons pins
#define OK_BTN_PIN A3
#define UP_BTN_PIN A1
#define DOWN_BTN_PIN A6
#define LEFT_BTN_PIN A2
#define RIGHT_BTN_PIN A7

// Display pins
#define TFT_CS D9
#define TFT_DC D10
#define TFT_RST D11
#define TFT_MOSI D12
#define TFT_SCLK D13

// SD card
#define SD_CARD_MISO D2
#define SD_CARD_SCK D3
#define SD_CARD_MOSI D4
#define SD_CARD_CS D5

#define CC1101_GDO0 A0
#define CC1101_CSN D7

#define PN532_SCL A4
#define PN532_SDA A5
#endif