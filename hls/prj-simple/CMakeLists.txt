cmake_minimum_required(VERSION 3.0)

project(prj_simple)

set(CMAKE_PREFIX_PATH "/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -lm")

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES    main.cpp)

add_executable(prj_simple ${SOURCE_FILES})

INCLUDE_DIRECTORIES(/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/)
