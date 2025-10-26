#!/usr/bin/env bash

directory="./bin"
if [ ! -d "$directory" ]; then
    mkdir -p "$directory"
fi
rm -rf ./bin/res
cp ./build/Forradia ./bin/
cp -r ./Resources ./bin/
cp -r ./code/theme_0_scripts/src/ ./bin/Resources/theme_0_scripts
cd ./bin
./Forradia
