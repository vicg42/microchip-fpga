cmake_minimum_required(VERSION 3.0)

project(axi_width_convert)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -lm")

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES  axi_width_convert.cpp)

add_executable(axi_width_convert ${SOURCE_FILES})

INCLUDE_DIRECTORIES(/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/)
INCLUDE_DIRECTORIES(/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/precompiled_sw_libraries/opencv4.5.4-x86_64-linux/include/opencv4/)
INCLUDE_DIRECTORIES(../include)

target_link_libraries(axi_width_convert -lpthread)
target_link_libraries(axi_width_convert -L/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/hls/)

target_link_libraries(axi_width_convert -L/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/precompiled_sw_libraries/opencv4.5.4-x86_64-linux/lib)
target_link_libraries(axi_width_convert -lopencv_core -lopencv_imgcodecs -lopencv_imgproc)
