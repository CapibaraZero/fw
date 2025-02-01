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

#include "SubGHZ.hpp"

#include <Arduino.h>

#include <vector>

#include "../../include/pins.h"

SPIClass SPI2(HSPI);

#ifndef CC1101_SUBGHZ
// TODO: Initialize SPI(and SX1276) in constructor of SubGHZ class
SX1276 radio =
    new Module(SX1276_NSS, RADIOLIB_NC, RADIOLIB_NC, SX1276_DIO1, SPI2);
#else
CC1101 radio = new Module(CC1101_CS, CC1101_IO0, -1, CC1101_IO2, SPI2);
#endif

#ifndef CC1101_SUBGHZ
// this function is called when a new bit is received
void IRAM_ATTR readBit(void) {
  // read the data bit
  radio.readBit(SX1276_DIO2);
}
#endif

SubGHZ::SubGHZ(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t csn,
               uint8_t gdo0, uint8_t gdo2) {
  if (initialized) return;
  pinMode(csn, OUTPUT);
  _csn = csn;
  _gdo0 = gdo0;
  _gdo2 = gdo2;
  initialized = true;
}

SubGHZ::~SubGHZ() {}

void SubGHZ::error_check(const char *operation, int16_t status_code) {
  if (status_code != RADIOLIB_ERR_NONE) {
    Serial.print(operation);
    Serial.print(" : ");
    Serial.print(F("failed, code "));
    Serial.println(status_code);
  }
}

void SubGHZ::init_receive() {
  if (_modulation == 2)  // LoRa doesn't require anything
    return;
#ifndef CC1101_SUBGHZ
  SPI2.begin(SX1276_SCK, SX1276_MISO, SX1276_MOSI, _csn);
  radio.beginFSK();
  radio.setCRC(false);
  radio.setAFC(true);
  radio.setDirectAction(readBit);
#else
  // Set antenna frequency settings
  pinMode(CC1101_SW1, OUTPUT);
  pinMode(CC1101_SW0, OUTPUT);

  digitalWrite(CC1101_SW1, HIGH);
  digitalWrite(CC1101_SW0, HIGH);

  SPI2.begin(CC1101_SCK, CC1101_MISO, CC1101_MOSI, _csn);

  int state = radio.begin(433.92);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("Error initializing CC1101");
    Serial.printf("Status: %i\n", state);
  } else {
    Serial.println("Initialized correctly");
  }

  state = radio.setFrequency(433.92);
  error_check("Set frequency", state);

  state = radio.setOOK(true);
  error_check("Set OOK", state);

  // set bit rate to 100.0 kbps
  state = radio.setBitRate(50);
  error_check("Set bitrate", state);

  state = radio.setRxBandwidth(812.50);
  error_check("Set RX Bandwidth", state);

  state = radio.setFrequencyDeviation(47.60);
  error_check("Set frequency deviation", state);

  state = radio.setOutputPower(12);
  error_check("Set output power", state);
  
  state = radio.setEncoding(RADIOLIB_ENCODING_NRZ);
  error_check("Set encoding", state);

  state = radio.variablePacketLengthMode();
  error_check("set variable length", state);

  state = radio.setCrcFiltering(false);
  error_check("Disable CRC", state);

#endif
  radio.setDirectSyncWord(0x555512AD, 0);
  radio.receiveDirect();
}

int16_t SubGHZ::get_chip_version() {
  int16_t version = 0;
#ifndef CC1101_SUBGHZ
  SPI2.begin(SX1276_SCK, SX1276_MISO, SX1276_MOSI, _csn);
  if(radio.beginFSK() == RADIOLIB_ERR_NONE) {
    version = radio.getChipVersion();
  }
#else
  SPI2.begin(CC1101_SCK, CC1101_MISO, CC1101_MOSI, _csn);
  digitalWrite(CC1101_CS, HIGH);

  int state = radio.begin(315);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("Error initializing CC1101");
    Serial.printf("Status: %i\n", state);
  } else {
    Serial.println("Initialized correctly");
    version = radio.getChipVersion();
  }
#endif
  return version;
}

void SubGHZ::stop_receive() {
#ifdef ESP32S3_DEVKITC_BOARD
  radio.clearDio1Action();
  radio.clearDio0Action();
#endif
#ifdef ARDUINO_NANO_ESP32
  ESP.restart();  // Dirty hack to reset SX1276. SX1276 when read the packet
                  // never stops to use SPI even after a radio.sleep()
#endif
}

void SubGHZ::set_freq_mod(float freq, float bw, float deviation) {
  int state = 0;
#ifdef CC1101_SUBGHZ
  if ((freq >= 300.0) && (freq <= 348.0)) {
    digitalWrite(CC1101_SW1, HIGH);
    digitalWrite(CC1101_SW0, LOW);
  } else if ((freq >= 387.0) && (freq <= 464.0)) {
    digitalWrite(CC1101_SW1, HIGH);
    digitalWrite(CC1101_SW0, HIGH);
  } else if ((freq >= 779.0) && (freq <= 928.0)) {
    digitalWrite(CC1101_SW1, LOW);
    digitalWrite(CC1101_SW0, HIGH);
  }
#else
  state = radio.setFrequency(freq);
  error_check("Set frequency", state);
  if (_modulation != 2) {
    state = radio.setRxBandwidth(bw);
    error_check("Set bandwidth", state);
    state = radio.setFrequencyDeviation(deviation);
    error_check("Set deviation", state);
  }
  _deviation = deviation;
  _bw = bw;
#endif
  _frequency = freq;
  delay(10);  // Time to adjust frequency(from: https://github.com/pr3y/Bruce/blob/main/src/modules/rf/rf.cpp#L205)
}

float SubGHZ::get_rssi() {
  float rssi = 0;
#ifndef CC1101_SUBGHZ
  rssi = radio.getRSSI(false, false);
#else
  rssi = radio.getRSSI();
#endif
  return rssi;
}

SignalStrength SubGHZ::scan_frequency(float freq, float bw, float deviation) {
  set_freq_mod(freq, bw, deviation);
  return SignalStrength{.rssi = get_rssi()};
}

SignalStrength SubGHZ::scan_frequency() {
  return SignalStrength{.rssi = get_rssi()};
}

#ifndef CC1101_SUBGHZ
#define DEFAULT_SAMPLING_RATE 50

#define READ_N_BYTE() for (int j = 7; j > -1; j--)

void read_lora_packet(std::vector<byte> *orig_signal) {
  // TODO: Add DIO0 and use it as interrupt

  // you can also receive data as byte array
  size_t len = radio.getPacketLength();
  byte byteArr[len];
  int state = radio.receive(byteArr, len);

  if (state == RADIOLIB_ERR_NONE) {
    // packet was successfully received
    Serial.println(F("Packet arrived!"));
    memcpy(orig_signal->data(), byteArr, len);
  } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
    // timeout occurred while waiting for a packet
    Serial.println(F("timeout!"));

  } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
    // packet was received, but is malformed
    Serial.println(F("CRC error!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);
  }
}
#endif

void SubGHZ::rec_signal(std::vector<byte> *orig_signal) {
#ifndef CC1101_SUBGHZ
  if (_modulation == 2) {  // LoRa modulation
    while (true) {
      read_lora_packet(orig_signal);
    }
  }
#endif
  if (radio.available()) {
    Serial.println("Received packet in direct mode!");
    while (radio.available()) {
      // read a byte
      byte signal = radio.read();
      orig_signal->push_back(signal);
    }
  }
}

void SubGHZ::send_signal(float freq, Modulation modulation, byte *payload,
                         size_t length) {
  set_modulation(modulation.mode);
  set_freq_mod(freq, modulation.bandwidth, modulation.deviation);
  int state = radio.transmit(payload, length);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("Transimt successfully!"));

  } else if (state == RADIOLIB_ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 256 bytes
    Serial.println(F("too long!"));
  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);
  }
};

void SubGHZ::set_modulation(int mod) {
  int state = RADIOLIB_ERR_NONE;
#ifndef CC1101_SUBGHZ
  /* Module was on LoRA*/
  if (_modulation == 2 && mod != 2) {
    state = radio.beginFSK();
    error_check("Begin FSK", state);
  }
#endif

  _modulation = mod;

  if (!mod)
    state = radio.setOOK(true);
  else if (mod == 1)
    state = radio.setOOK(false);
#ifndef CC1101_SUBGHZ
  else {
    state = radio.begin();
    error_check("Begin LoRa", state);
    return;
  }
#endif
  error_check("Set modulation", state);
}
