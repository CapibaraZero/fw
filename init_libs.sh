#!/bin/bash

echo "Downloading duktape..."
wget https://duktape.org/duktape-2.7.0.tar.xz -O duktape-2.7.0.tar.xz

echo "Preparing extraction folder..."
mkdir -p lib/duktape-2.7.0

echo "Extracting duktape..."
tar -xvf duktape-2.7.0.tar.xz -C lib/duktape-2.7.0 --strip-components=1

echo "Cleanup..."
rm -rf duktape-2.7.0.tar.xz