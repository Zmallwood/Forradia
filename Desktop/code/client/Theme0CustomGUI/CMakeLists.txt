cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaTheme0CustomGUI ${SOURCES})
target_include_directories(ForradiaTheme0CustomGUI PUBLIC
    "./src"
)
target_link_libraries(ForradiaTheme0CustomGUI PRIVATE
    ForradiaEngine
    ForradiaTheme0WorldStructure
    ForradiaTheme0Essentials
    ForradiaTheme0Core
)
target_precompile_headers(ForradiaTheme0CustomGUI PUBLIC ./src/PCH.hpp)
