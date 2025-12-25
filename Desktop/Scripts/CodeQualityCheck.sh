#!/usr/bin/env bash
cd ..
shopt -s globstar  # Enable recursive globbing
INCLUDE_FLAGS=$(find code/client -type d -name "src" -exec printf -- "--extra-arg=-I%s " {} \;)
clang-tidy code/client/RiverDiggerTheme/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20