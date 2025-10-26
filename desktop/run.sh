#!/usr/bin/env bash

directory="./bin"
if [ ! -d "$directory" ]; then
    mkdir -p "$directory"
fi
rm -rf ./bin/Resources
cp ./build/Forradia ./bin/
cp -r ./Resources ./bin/
cp -r ./code/theme_0_scripts/src/ ./bin/Resources/Theme0Scripts
cd ./bin
./Forradia
