#!/bin/bash

# Script used to format all files using clang-format

files=$(find . -type f)

for file in $files
do
if [[ $file != *".git"* && $file != *".vscode"* && $file != *".pio"* && $file != *"Library"* && $file != *"BusIO"*  && $file != *".csv"* && ($file == *".c"* || $file == *".h"*) ]]; then
    echo "Formatting $file"
    clang-format -style=Google -i "$file"
fi
done