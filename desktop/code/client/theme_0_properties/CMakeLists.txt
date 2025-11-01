cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE THEME_0_PROPERTIES "./src/*.cpp")
add_library(ForradiaTheme0Properties ${THEME_0_PROPERTIES})
target_include_directories(ForradiaTheme0Properties PUBLIC
    "../theme_0_properties/src"
    "../common_lang/src"
    "../common_matter/src"
    "../common_general/src"
)
target_precompile_headers(ForradiaTheme0Properties PUBLIC ./src/StdAfx.hpp)
