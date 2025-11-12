#!/usr/bin/env bash

cd ..

directory="./bin"

if [ ! -d "$directory" ]; then
    mkdir -p "$directory"
fi

rm -rf ./bin/Resources
cp ./build/client/theme_0/Forradia ./bin/
cp -r ./Resources ./bin/
cp -r ./code/client/Theme0Scripts/src/ ./bin/Resources/Theme0Scripts
cd ./bin

./Forradia
