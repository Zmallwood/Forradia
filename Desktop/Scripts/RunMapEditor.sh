#!/usr/bin/env bash

cd ..

directory="./bin"

if [ ! -d "$directory" ]; then
    mkdir -p "$directory"
fi

cp ./build/map_editor/ForradiaMapEditor ./bin/
cd ./bin

./ForradiaMapEditor
