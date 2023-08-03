cmake_minimum_required(VERSION 3.0)

project(prj_canny)

set(CMAKE_PREFIX_PATH "/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -lm")

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES    canny.cpp
                    gaussian_filter.cpp
                    gf_sw.cpp
                    hf_sw.cpp
                    hysteresis_filter.cpp
                    nm_sw.cpp
                    nonmaximum_suppression.cpp
                    sf_sw.cpp
                    sobel_filter.cpp
                    util.cpp)

add_executable(prj_canny ${SOURCE_FILES})

INCLUDE_DIRECTORIES(/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/)
