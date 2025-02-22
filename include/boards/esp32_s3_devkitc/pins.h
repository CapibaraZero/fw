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

// Set your display resolution here
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 240

// Define buttons pins
#define OK_BTN_PIN 40
#define UP_BTN_PIN 47
#define DOWN_BTN_PIN 41
#define LEFT_BTN_PIN 39
#define RIGHT_BTN_PIN 42

// Display pins
#define TFT_RST 5
#define TFT_DC 4
#define TFT_CS 10
#define TFT_MOSI 11
#define TFT_MISO -1
#define TFT_SCLK 12
#define TFT_BLK 48

// SD card
#define SD_CARD_CS 13
#define SD_CARD_MOSI 35
#define SD_CARD_SCK 36
#define SD_CARD_MISO 37

#define SX1276_NSS 1
#define SX1276_DIO2 15
#define SX1276_DIO1 16
#define SX1276_SCK 17
#define SX1276_MOSI 18
#define SX1276_MISO 7

#define PN532_SDA 8
#define PN532_SCL 9
#define PN532_RST -1
#define PN532_IRQ -1

#define BATTERY_MONITOR 2

#define IR_RECEIVER_PIN 6
#define IR_EMITTER_PIN 14
