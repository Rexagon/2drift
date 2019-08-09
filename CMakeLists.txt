cmake_minimum_required(VERSION 3.14)
project(2drift)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 CONFIG REQUIRED COMPONENTS
        system
        window
        network
        graphics
        audio)

find_package(EnTT REQUIRED)

set(BUILD_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)

add_subdirectory(src/Core)
add_subdirectory(src/Game)
