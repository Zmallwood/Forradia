cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



add_library(ForradiaComm src_comm/comm.cpp)

target_link_libraries(ForradiaComm PRIVATE SDL2 SDL2_image SDL2_ttf fmt)



add_library(ForradiaWorldStruct src_world_struct/world_struct.cpp)

target_include_directories(ForradiaWorldStruct PRIVATE "src_comm")

target_link_libraries(ForradiaWorldStruct ForradiaComm)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Forradia ${SOURCES})

target_include_directories(Forradia PRIVATE "src")
target_include_directories(Forradia PRIVATE "src_comm")
target_include_directories(Forradia PRIVATE "src_world_struct")

target_link_libraries(Forradia PRIVATE ForradiaComm ForradiaWorldStruct)

#add_definitions(-include std_afx.hpp)
#add_definitions(-include ../src_comm/comm.hpp)
#add_definitions(-include ../src_world_struct/world_struct.hpp)

#target_precompile_headers(Forradia PRIVATE src/std_afx.hpp)

install(TARGETS Forradia RUNTIME DESTINATION bin)
