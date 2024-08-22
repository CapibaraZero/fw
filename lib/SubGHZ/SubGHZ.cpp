#include "SubGHZ.hpp"
#include <Arduino.h>
#include <vector>
#include "../../include/pins.h"

SPIClass SPI2(HSPI);

// TODO: Initialize SPI(and SX1276) in constructor of SubGHZ class
SX1276 radio = new Module(SX1276_NSS, RADIOLIB_NC, RADIOLIB_NC, SX1276_DIO1, SPI2);

// this function is called when a new bit is received
void IRAM_ATTR readBit(void) {
    // read the data bit
    radio.readBit(SX1276_DIO2);
}

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
    if (_modulation == 2)   // LoRa doesn't require anything
        return;
    SPI2.begin(SD_CARD_SCK, SX1276_MISO, SD_CARD_MOSI, _csn);
    radio.beginFSK();
    radio.setCRC(false);
    radio.setAFC(true);
    radio.setDirectSyncWord(0x555512AD, 0);
    radio.setDirectAction(readBit);
    radio.receiveDirect();
}

void SubGHZ::stop_receive() {
#ifdef ESP32S3_DEVKITC_BOARD
    radio.clearDio1Action();
    radio.clearDio0Action();
#endif
#ifdef ARDUINO_NANO_ESP32
    ESP.restart();  // Dirty hack to reset SX1276. SX1276 when read the packet never stops to use SPI even after a radio.sleep()
#endif
}

void SubGHZ::set_freq_mod(float freq, float bw, float deviation) {
    int state = radio.setFrequency(freq);
    error_check("Set frequency", state);
    if (_modulation != 2) {
        state = radio.setRxBandwidth(bw);
        error_check("Set bandwidth", state);
        state = radio.setFrequencyDeviation(deviation);
        error_check("Set deviation", state);
        _deviation = deviation;
    }
    _frequency = freq;
    _bw = bw;
}

SignalStrength SubGHZ::scan_frequency(float freq, float bw, float deviation) {
    set_freq_mod(freq, bw, deviation);
    return SignalStrength{.rssi = radio.getRSSI(false, false)};
}

SignalStrength SubGHZ::scan_frequency() {
    return SignalStrength{.rssi = radio.getRSSI(false, false)};
}

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

void SubGHZ::rec_signal(std::vector<byte> *orig_signal) {
    if (_modulation == 2) {  // LoRa modulation
        while (true) {
            read_lora_packet(orig_signal);
        }
    }
    if (radio.available()) {
        Serial.println("[SX1276] Received packet in direct mode!");
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
    }
    else {
        // some other error occurred
        Serial.print(F("failed, code "));
        Serial.println(state);
    }
};

void SubGHZ::set_modulation(int mod) {
    int state = RADIOLIB_ERR_NONE;
    /* Module was on LoRA*/
    if (_modulation == 2 && mod != 2) {
        state = radio.beginFSK();
        error_check("Begin FSK", state);
    }

    _modulation = mod;

    if (!mod)
        state = radio.setOOK(true);
    else if (mod == 1)
        state = radio.setOOK(false);
    else {
        state = radio.begin();
        error_check("Begin LoRa", state);
        return;
    }
    error_check("Set modulation", state);
}
