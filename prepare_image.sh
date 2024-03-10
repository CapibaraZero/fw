#!/bin/bash

# A simple script to extract build images from pio folder

cp /Users/andreock/.platformio/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin build/
cp .pio/build/esp32-s3-devkitc-1/partitions.bin build/
cp .pio/build/esp32-s3-devkitc-1/firmware.bin build/
cp .pio/build/esp32-s3-devkitc-1/bootloader.bin build/