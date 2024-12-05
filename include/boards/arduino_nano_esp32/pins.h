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
#define OK_BTN_PIN A3
#define UP_BTN_PIN A5
#define DOWN_BTN_PIN A2
#define LEFT_BTN_PIN A4
#define RIGHT_BTN_PIN A1

// Display pins
#define TFT_CS D6
#define TFT_DC D5
#define TFT_RST -1
#define TFT_MOSI D2
#define TFT_MISO -1
#define TFT_SCLK D4

// SD card
#define SD_CARD_CS D10
#define SD_CARD_MOSI D11
#define SD_CARD_MISO D12
#define SD_CARD_SCK D13

// SX1276(SubGHZ)
#define SX1276_DIO1 D0
#define SX1276_NSS D7
#define SX1276_DIO2 D1
#define SX1276_SCK SD_CARD_SCK
#define SX1276_MOSI SD_CARD_MOSI
#define SX1276_MISO D9

// PN532(NFC)
#define PN532_SCL A6
#define PN532_SDA A7

#define BATTERY_MONITOR A0

#define IR_RECEIVER_PIN D8
#define IR_EMITTER_PIN D3