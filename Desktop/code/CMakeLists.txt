cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(./client/Theme0WorldGenerationCommon/)
add_subdirectory(./client/Theme0WorldGenerationGround/)
add_subdirectory(./client/Theme0WorldGenerationWater/)
add_subdirectory(./client/Theme0WorldGenerationObjects/)
add_subdirectory(./client/Theme0WorldGenerationEntities/)
add_subdirectory(./client/Theme0WorldGenerationMain/)
add_subdirectory(./client/Theme0Essentials/)
add_subdirectory(./client/ForradiaEngine/)
add_subdirectory(./client/Theme0Core/)
add_subdirectory(./client/Theme0CustomGUI/)
add_subdirectory(./client/RiverDiggerTheme/)

install(TARGETS RiverDigger RUNTIME DESTINATION bin)
