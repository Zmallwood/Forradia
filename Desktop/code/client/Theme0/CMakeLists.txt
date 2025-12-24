cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_executable(Forradia ${SOURCES})
#target_link_libraries(Forradia PRIVATE )
target_precompile_headers(Forradia PUBLIC ./src/PCH.hpp)
target_include_directories(Forradia PUBLIC
    "./src"
)
target_link_libraries(Forradia PRIVATE
    ForradiaTheme0WorldStructure
    ForradiaTheme0WorldGenerationMain
    ForradiaTheme0Essentials
    ForradiaCoreEngine
    ForradiaTheme0Properties
    ForradiaTheme0Core
    ForradiaTheme0CustomGUI
    ForradiaTheme0Scenes
    SDL2
    SDL2_image
    SDL2_ttf
    GL
    GLEW
    fmt
)

file(COPY ${CMAKE_SOURCE_DIR}/../Resources
        DESTINATION ${CMAKE_BINARY_DIR}/client/Theme0)