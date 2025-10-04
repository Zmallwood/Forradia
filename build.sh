#!/usr/bin/env bash
cd build
cmake ..
cmake --build .
cd ..
directory="./bin"
if [ ! -d "$directory" ]; then
    mkdir -p "$directory"
fi
cp ./build/Forradia ./bin/
cp -r ./res ./bin/