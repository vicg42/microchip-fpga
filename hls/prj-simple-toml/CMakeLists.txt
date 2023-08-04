cmake_minimum_required(VERSION 3.0)

project(main)

include_directories("../libraries/toml11-3.7.1/")
include_directories("../libraries/tclap-1.2.5/include/")

# set(CMAKE_PREFIX_PATH "/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -lm")

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES    main.cpp
                    parsingComLine.cpp)

add_executable(main ${SOURCE_FILES})

# INCLUDE_DIRECTORIES(/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/)
