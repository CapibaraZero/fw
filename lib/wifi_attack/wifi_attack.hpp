/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or https://capibarazero.github.io/).
 * Copyright (c) 2023 Andrea Canale.
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

#ifndef WIFIATTACK_H
#define WIFIATTACK_H

#include "wifi_sniffer.hpp"
#include "../../include/WifiNetwork.hpp"
#include <vector>
#include "FS.h"

using namespace std;

class WifiAttack
{
private:
    void rotate_all_channels(int max_ch, int wait_time);
public:
    WifiAttack(/* args */);
    ~WifiAttack();

    
    /// @brief Scan all the WiFi environments
    /// @return A list of all network found
    vector<WifiNetwork> scan();
    /// @brief Save WiFI scan result to JSON in SD
    /// @param networks WiFi scan result
    void save_scan(vector<WifiNetwork> *networks);

    /// @brief Sniff all the WiFi environment and save it to SD
    /// @param delay Time before switch to another channel
    /// @param inf Sniff all the time
    void sniff(int delay, bool inf, FS sd);


    /// @brief Sniff a specific WiFi channel range and save it to SD
    /// @param max_ch Maximium channel that it will scan
    /// @param delay Time before switch to another channel
    /// @param inf Sniff all the time
    void sniff(int max_ch, int delay, bool inf, FS sd);


    /// @brief Sniff a specific WiFi channel
    /// @param channel WiFi channel to sniff
    /// @param time Time before finish scan. Not used in case of inf==true
    /// @param inf Sniff all the time
    void sniff_channel(int channel, int time, bool inf, FS sd);
};

#endif