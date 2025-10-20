#!/usr/bin/env bash

directory="./bin"
if [ ! -d "$directory" ]; then
    mkdir -p "$directory"
fi
rm -rf ./bin/res
cp ./build/Forradia ./bin/
cp -r ./res ./bin/
cp -r ./code/theme_0_scripts/src/ ./bin/res/theme_0_scripts
cd ./bin
./Forradia