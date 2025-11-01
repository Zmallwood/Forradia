cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE THEME_0_ESSENTIALS_SOURCES "./src/*.cpp")
add_library(ForradiaTheme0Essentials ${THEME_0_ESSENTIALS_SOURCES})
target_include_directories(ForradiaTheme0Essentials PUBLIC
    "../common_lang/src"
    "../theme_0_world_struct/src"
)
target_link_libraries(ForradiaTheme0Essentials
    ForradiaCoreRendering
    ForradiaTheme0WorldStruct
)
target_precompile_headers(ForradiaTheme0Essentials PUBLIC ./src/StdAfx.hpp)
