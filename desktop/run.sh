#!/usr/bin/env bash

directory="./bin"
if [ ! -d "$directory" ]; then
    mkdir -p "$directory"
fi
cp ./build/Forradia ./bin/
cp -r ./res ./bin/
cd ./bin
./Forradia