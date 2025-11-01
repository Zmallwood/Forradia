#!/usr/bin/env bash
cd ../build
cmake ../code
cmake --build . --parallel 4
