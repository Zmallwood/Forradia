cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(ForradiaComm src_comm/comm.cpp)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(ForradiaComm PRIVATE ${PYTHON_LIBRARIES})

target_link_libraries(ForradiaComm PRIVATE SDL2 SDL2_image SDL2_ttf fmt GL GLEW)




file(GLOB_RECURSE ENGINE_SOURCES "src_engine/*.cpp")

add_library(ForradiaEngine ${ENGINE_SOURCES})

target_include_directories(ForradiaEngine PRIVATE "src_comm")

target_link_libraries(ForradiaEngine ForradiaComm)




add_library(ForradiaTheme0WorldStruct src_theme_0_world_struct/world_struct.cpp)

target_include_directories(ForradiaTheme0WorldStruct PRIVATE "src_comm")

target_link_libraries(ForradiaTheme0WorldStruct ForradiaComm)






file(GLOB_RECURSE SOURCES "src_theme_0/*.cpp")

add_executable(Forradia ${SOURCES})




target_include_directories(Forradia PRIVATE
    "src_theme_0"
    "src_comm"
    "src_engine"
    "src_theme_0_world_struct"
)

target_link_libraries(Forradia PRIVATE
    ForradiaComm
    ForradiaEngine
    ForradiaTheme0WorldStruct
)

install(TARGETS Forradia RUNTIME DESTINATION bin)
