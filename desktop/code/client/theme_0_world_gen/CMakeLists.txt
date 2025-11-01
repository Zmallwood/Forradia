cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE WORLD_GEN_SOURCES "./src/*.cpp")
add_library(ForradiaTheme0WorldGen ${WORLD_GEN_SOURCES})
target_include_directories(ForradiaTheme0WorldGen PUBLIC
    "../theme_0_world_gen/src"
    "../theme_0_properties/src"
)
target_link_libraries(ForradiaTheme0WorldGen ForradiaTheme0WorldStruct)
target_precompile_headers(ForradiaTheme0WorldGen PUBLIC ./src/StdAfx.hpp)
