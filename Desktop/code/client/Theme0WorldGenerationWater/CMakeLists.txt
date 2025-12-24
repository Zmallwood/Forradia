cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaTheme0WorldGenerationWater ${SOURCES}
        src/WorldGeneratorWater_GenerateRiverFromSource_Sub.hpp)
target_include_directories(ForradiaTheme0WorldGenerationWater PUBLIC
    "./src"
)
target_link_libraries(ForradiaTheme0WorldGenerationWater PRIVATE
    ForradiaEngine
    ForradiaTheme0WorldGenerationCommon
    RiverDiggerLib
)
target_precompile_headers(ForradiaTheme0WorldGenerationWater PUBLIC ./src/PCH.hpp)
