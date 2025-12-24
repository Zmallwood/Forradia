cmake_minimum_required(VERSION 3.5)

project(Forradia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------------------------
# Library
# -------------------------------------------------

file(GLOB_RECURSE RIVERDIGGER_LIB_SOURCES
    "./src/*.cpp"
)

# Remove main.cpp from the library sources
list(FILTER RIVERDIGGER_LIB_SOURCES EXCLUDE REGEX ".*Main\\.cpp$")

add_library(RiverDiggerLib STATIC ${RIVERDIGGER_LIB_SOURCES})

target_include_directories(RiverDiggerLib
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_precompile_headers(RiverDiggerLib
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PCH.hpp"
)

target_link_libraries(RiverDiggerLib
    PUBLIC
        ForradiaEngine
        SDL2
        SDL2_image
        SDL2_ttf
        GL
        GLEW
        fmt
)

# -------------------------------------------------
# Executable
# -------------------------------------------------

add_executable(RiverDigger
    src/Main.cpp
)

target_link_libraries(RiverDigger
    PRIVATE
        RiverDiggerLib
)

# -------------------------------------------------
# Resources
# -------------------------------------------------

file(COPY
    ${CMAKE_SOURCE_DIR}/../Resources
    DESTINATION ${CMAKE_BINARY_DIR}/client/Theme0
)
