#!/bin/bash
# From: https://skylab.hashnode.dev/platformio-with-neovim-cll831tnz000209me4xds9h2j
# Ported to MacOS

DEVICE=$1

# Compile the project
pio run -t compiledb -e $DEVICE

# Clean up existing define files
rm -f _compiler_defines.h compiler_defines.h clang_defines.h

# Generate defines for clang
clang -dM -xc++ /dev/null -c -v -E 2>/dev/null | sed "s/\([^[:space:]]\+[[:space:]]\+[^[:space:]]\+\)\(.*\)/\1/;s/#define/#undef/" >clang_defines.h

# Iterate through compile_commands.json and extract compiler defines
for comp in $(cat compile_commands.json | grep -E "\"command\": \"[^[:space:]]* -o" | sed 's:"command"\: "::g; s:-o.*::g' | sort | uniq); do
    set -x
    $comp -dM -E -xc++ /dev/null >>_compiler_defines.h
    set +x
done

# Combine defines from clang and extracted defines
cat clang_defines.h >compiler_defines.h
cat _compiler_defines.h | sort | uniq >>compiler_defines.h

# Clean up temporary define files
rm -f _compiler_defines.h clang_defines.h

case "$OSTYPE" in
  darwin*|bsd*)
    sed_option=( -i '' )
    ;; 
  *)
    sed_option=( -i )
    ;;
esac

# Update compile_commands.json with additional include flags
sed $sed_option -e "s:.cpp\",:.cpp -include $${PWD}/compiler_defines.h\",:" compile_commands.json
sed $sed_option -e "s:.c\",:.c -include $${PWD}/compiler_defines.h\",:" compile_commands.json

