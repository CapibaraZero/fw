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

#ifndef SUBGHZ_LIBRARY_H
#define SUBGHZ_LIBRARY_H

#include <Arduino.h>
#include <RadioLib.h>

#include <vector>

// enum ModulationMode { ASK, FSK };

typedef struct Modulation {
  int mode;
  float deviation;
  float bandwidth;
} Modulation;

typedef struct Signal {
  int modulation;
  float frequency;
  uint8_t *payload;
} Signal;

typedef struct SignalStrength {
  float rssi;
} SignalStrength;

class SubGHZ {
 private:
  byte jammer_payload[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  int _gdo0 = -1;
  int _gdo2 = -1;
  int _csn = -1;
  float _frequency;
  float _bw;
  float _deviation;
  int _modulation;
  bool initialized = false;
  void error_check(const char *operation, int16_t status_code);
  float get_rssi();

 public:
  SubGHZ(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t csn, uint8_t gdo0,
         uint8_t gdo2);
  ~SubGHZ();
  // Getter functions
  float get_frequency() { return _frequency; };
  float get_bw() { return _bw; };
  float get_deviation() { return _deviation; };
  int get_modulation() { return _modulation; };
  void init_receive();
  void stop_receive();
  void set_freq_mod(float freq, float bw, float deviation);
  SignalStrength scan_frequency(float freq, float bw = 200.0F,
                                float deviation = 47.0F);
  SignalStrength scan_frequency();
  int16_t get_chip_version();
  void rec_signal(std::vector<byte> *orig_signal);
  void send_signal(float freq, Modulation modulation, byte *payload,
                   size_t length);
  /// @brief Set modulation to ASK or FSK
  /// @param mod 0 for ASK, 1 for FSK and 2 for LoRA
  void set_modulation(int mod);
};

#endif