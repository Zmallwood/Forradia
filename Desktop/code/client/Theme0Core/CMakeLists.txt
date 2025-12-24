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
    ForradiaTheme0Essentials
    ForradiaEngine
    ForradiaTheme0CustomGUI
    RiverDiggerLib
)
target_precompile_headers(ForradiaTheme0Core PUBLIC ./src/PCH.hpp)
