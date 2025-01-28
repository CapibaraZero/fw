#!/bin/bash

# A simple script to extract firmware images from pio folder
BOARD=$1
VERSION="0_5_2"
# mkdir firmware

# Remove old firmware
# rm -rf firmware/*

# pio run -e "$BOARD"

cp /home/"$(whoami)"/.platformio/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin firmware/"$BOARD"
cp .pio/build/"$BOARD"/partitions.bin firmware/"$BOARD"
cp .pio/build/"$BOARD"/firmware.bin firmware/"$BOARD"
cp .pio/build/"$BOARD"/bootloader.bin firmware/"$BOARD"

# cd firmware && zip -9 -r capibaraZero_"$VERSION"_"$BOARD".zip *
