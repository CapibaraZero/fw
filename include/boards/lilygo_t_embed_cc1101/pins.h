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
#define DISPLAY_WIDTH 170
#define DISPLAY_HEIGHT 320

// Define buttons pins
#define OK_BTN_PIN 0

#define ENCODER_A_PIN 4
#define ENCODER_B_PIN 5

#define STANDBY_BTN 6
#define WAKEUP_PIN 0

// Display pins
#define TFT_CS 41
#define TFT_DC 16
#define TFT_RST -1
#define TFT_MOSI 9
#define TFT_MISO 10
#define TFT_SCLK 11
#define TFT_BLK 21

// SD card
#define SD_CARD_CS 13
#define SD_CARD_MOSI 9
#define SD_CARD_MISO 10
#define SD_CARD_SCK 11

// SX1276(SubGHZ)
#define CC1101_MOSI 9
#define CC1101_MISO 10
#define CC1101_SCK 11
#define CC1101_CS 12
#define CC1101_IO2 38
#define CC1101_IO0 3
#define CC1101_SW1 47
#define CC1101_SW0 48

// PN532(NFC)
#define NFC_BUS_SCL 18
#define NFC_BUS_SDA 8
#define PN532_RST 45
#define PN532_IRQ 17

#define BOARD_PWR_EN 15
#define BQ27220_BATTERY

#define IR_RECEIVER_PIN 1
#define IR_EMITTER_PIN 2