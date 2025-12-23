cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaTheme0Core ${SOURCES})
target_include_directories(ForradiaTheme0Core PUBLIC
    "./src"
)
target_link_libraries(ForradiaTheme0Core PRIVATE
    ForradiaCommonGeneral
    ForradiaCommonMatter
    ForradiaCommonUtilities
    ForradiaCoreGUI
    ForradiaTheme0WorldStructure
    ForradiaTheme0Essentials
    ForradiaTheme0Properties
    ForradiaCoreRenderingGround
    ForradiaTheme0CustomGUI
    ForradiaCoreRenderingModels
    ForradiaCoreRenderingSky
)
target_precompile_headers(ForradiaTheme0Core PUBLIC ./src/StdAfx.hpp)
