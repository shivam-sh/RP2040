cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(Blink)

add_executable(blink
    blink.c
    )

target_link_libraries(blink pico_stdlib)

# pico_add_extra_outputs(blink)

# example_auto_set_url(blink)