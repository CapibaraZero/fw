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

#ifndef BLUETOOTHATTACKS_H
#define BLUETOOTHATTACKS_H

#include "AppleJuice.hpp"
#include "samsung_ble_spam.hpp"
#include "microsoft_ble_spam.hpp"
#include "FS.h"

class BluetoothAttack
{
private:
    AppleJuice appleJuice = AppleJuice();
    SamsungBleSpam samsung = SamsungBleSpam();
    MicrosoftBleSpam swift_pair = MicrosoftBleSpam();

public:
    BluetoothAttack()
    {
        NimBLEDevice::init("");
    };
    ~BluetoothAttack()
    {
        NimBLEDevice::deinit();
    };
    void appleJuiceAttack()
    {
        for (;;)
        {
            appleJuice.attack();
        }
    };
    void samsungBleSpamAttack()
    {
        for (;;)
        {
            samsung.attack();
        }
    };
    void swiftPairSpamAttack()
    {
        for (;;)
        {
            swift_pair.attack();
        }
    };

    void sniff(FS sd);
    void scan(FS sd, int scan_time = 30);
};

#endif