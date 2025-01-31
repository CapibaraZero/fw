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

// Set your display resolution here
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 240

// Define buttons pins
#define OK_BTN_PIN 13
#define UP_BTN_PIN 9
#define DOWN_BTN_PIN 8
#define LEFT_BTN_PIN 12
#define RIGHT_BTN_PIN 6

// Display pins
#define TFT_RST -1
#define TFT_DC 0
#define TFT_CS 1
#define TFT_MOSI 19
#define TFT_MISO -1
#define TFT_SCLK 18
// #define TFT_BLK 

// SD card
#define SD_CARD_CS 7
#define SD_CARD_MOSI 6
#define SD_CARD_SCK 4
#define SD_CARD_MISO 5

#define SX1276_NSS 1
#define SX1276_DIO2 15
#define SX1276_DIO1 16
#define SX1276_SCK SD_CARD_SCK
#define SX1276_MOSI SD_CARD_MOSI
#define SX1276_MISO SD_CARD_MISO

// Alternatively, you can use CC1101
// #define CC1101_MOSI 9
// #define CC1101_MISO 10
// #define CC1101_SCK 11
// #define CC1101_CS 12
// #define CC1101_IO2 38
// #define CC1101_IO0 3

#define PN532_SDA 4
#define PN532_SCL 5
#define PN532_RST -1
#define PN532_IRQ -1

// #define BATTERY_MONITOR 2

#define IR_RECEIVER_PIN 20
#define IR_EMITTER_PIN 21