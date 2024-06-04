#!/bin/bash

# A simple script to extract build images from pio folder
BOARD=$1
mkdir build

cp /Users/andreock/.platformio/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin build/
cp .pio/build/"$BOARD"/partitions.bin build/
cp .pio/build/"$BOARD"/firmware.bin build/
cp .pio/build/"$BOARD"/bootloader.bin build/

cd build && zip -9 -r capibaraZero_0_2_0_"$BOARD".zip *
