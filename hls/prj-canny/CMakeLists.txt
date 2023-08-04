cmake_minimum_required(VERSION 3.0)

project(canny)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -lm")

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES  canny.cpp
                  gaussian_filter.cpp
                  gf_sw.cpp
                  hf_sw.cpp
                  hysteresis_filter.cpp
                  nm_sw.cpp
                  nonmaximum_suppression.cpp
                  sf_sw.cpp
                  sobel_filter.cpp
                  util.cpp)

add_executable(canny ${SOURCE_FILES})

INCLUDE_DIRECTORIES(/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/)

target_link_libraries(canny -lpthread)
target_link_libraries(canny -L/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/hls/)
