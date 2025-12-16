#!/usr/bin/env bash
cd ..
mkdir -p ./build/
cd ./build
export CXX=clang++
cmake ../code
cmake --build . --parallel 4
