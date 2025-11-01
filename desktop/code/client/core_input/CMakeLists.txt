cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CORE_INPUT_SOURCES "./src/*.cpp")
add_library(ForradiaCoreInput ${CORE_INPUT_SOURCES})
target_include_directories(ForradiaCoreInput PUBLIC
    "../core_input/src"
)
target_precompile_headers(ForradiaCoreInput PUBLIC ./src/StdAfx.hpp)
