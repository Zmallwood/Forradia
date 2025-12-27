#!/usr/bin/env bash

docker run -d -v /home/andreas/code/git/Forradia/Desktop/code:/opengrok/src -p 8080:8080 opengrok/docker:latest