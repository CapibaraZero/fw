#!/bin/bash

git clone https://github.com/CapibaraZero/PN532.git
mv PN532/PN532 lib/
mv PN532/PN532_I2C lib/
rm -rf PN532