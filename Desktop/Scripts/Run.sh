#!/usr/bin/env bash

cd ..

directory="./bin"

if [ ! -d "$directory" ]; then
    mkdir -p "$directory"
fi

rm -rf ./bin/Resources
cp ./build/client/JewelryMakerTheme/JewelryMaker ./bin/
cp -r ./Resources ./bin/
cd ./bin

./JewelryMaker
