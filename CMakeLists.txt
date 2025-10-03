cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



add_library(ForradiaComm src_comm/comm.cpp)

target_link_libraries(ForradiaComm PRIVATE SDL2 SDL2_image SDL2_ttf fmt)




file(GLOB_RECURSE ENGINE_SOURCES "src_engine/*.cpp")

add_library(ForradiaEngine ${ENGINE_SOURCES})

target_include_directories(ForradiaEngine PRIVATE "src_comm")

target_link_libraries(ForradiaEngine ForradiaComm)




add_library(ForradiaTheme0WorldStruct src_theme_0_world_struct/world_struct.cpp)

target_include_directories(ForradiaTheme0WorldStruct PRIVATE "src_comm")

target_link_libraries(ForradiaTheme0WorldStruct ForradiaComm)






file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Forradia ${SOURCES})

target_include_directories(Forradia PRIVATE
    "src"
    "src_comm"
    "src_engine"
    "src_theme_0_world_struct"
)

target_link_libraries(Forradia PRIVATE
    ForradiaComm
    ForradiaEngine
    ForradiaTheme0WorldStruct
)

#add_definitions(-include std_afx.hpp)
#add_definitions(-include ../src_comm/comm.hpp)
#add_definitions(-include ../src_world_struct/world_struct.hpp)

#target_precompile_headers(Forradia PRIVATE src/std_afx.hpp)

install(TARGETS Forradia RUNTIME DESTINATION bin)
