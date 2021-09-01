cmake_minimum_required(VERSION 3.12)

set(PICO_BOARD "adafruit_feather_rp2040")

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set project name and C/C++ standards
project(edifier_remote C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# create pico_sdk subdirectory for the libraries
pico_sdk_init()

# Tell CMake where to find the source file
add_executable(${PROJECT_NAME}
    main.cpp
)

pico_add_extra_outputs(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
)