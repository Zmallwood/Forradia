cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaTheme0Scenes ${SOURCES})
target_include_directories(ForradiaTheme0Scenes PUBLIC
    "./src"
)
target_link_libraries(ForradiaTheme0Scenes PRIVATE
    ForradiaCommonGeneral
    ForradiaCommonMatter
    ForradiaTheme0Essentials
    ForradiaTheme0WorldGenerationMain
    ForradiaTheme0CustomGUI
    ForradiaTheme0Core
    ForradiaCoreRenderingImages2D
    ForradiaCoreRenderingGround
)
target_precompile_headers(ForradiaTheme0Scenes PUBLIC ./src/PCH.hpp)
