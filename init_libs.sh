#!/bin/bash

echo "Downloading duktape..."
wget https://duktape.org/duktape-2.7.0.tar.xz -O duktape-2.7.0.tar.xz
echo "Extracting duktape..."
tar -xvf duktape-2.7.0.tar.xz -C lib/duktape-2.7.0
echo "Cleanup..."
rm -rf duktape-2.7.0.tar.xz