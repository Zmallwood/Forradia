#!/usr/bin/env bash
cd ..
mkdir -p ./build/
cd ./build
export CXX=clang++
cmake -G Ninja ../code
cmake --build . --parallel 8
