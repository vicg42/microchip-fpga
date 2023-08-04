cmake_minimum_required(VERSION 3.0)

project(axis_video_ddr_tb)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -lm")

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES  axis_video_ddr_tb.cpp)

add_executable(axis_video_ddr_tb ${SOURCE_FILES})

INCLUDE_DIRECTORIES(/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/)
INCLUDE_DIRECTORIES(/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/precompiled_sw_libraries/opencv4.5.4-x86_64-linux/include/opencv4/)
INCLUDE_DIRECTORIES(../include)

target_link_libraries(axis_video_ddr_tb -lpthread)
target_link_libraries(axis_video_ddr_tb -L/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/smarthls-library/hls/)

target_link_libraries(axis_video_ddr_tb -L/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/precompiled_sw_libraries/opencv4.5.4-x86_64-linux/lib)
target_link_libraries(axis_video_ddr_tb -lopencv_core -lopencv_imgcodecs -lopencv_imgproc)
