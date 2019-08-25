cmake_minimum_required(VERSION 3.14)
project(2drift)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(EnTT REQUIRED)

set(BUILD_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)

add_subdirectory(extlibs/glad)
add_subdirectory(extlibs/stb)
add_subdirectory(src/Core)
add_subdirectory(src/Game)
