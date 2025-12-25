cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(./client/JewelryMakerTheme/)

install(TARGETS JewelryMaker RUNTIME DESTINATION bin)
