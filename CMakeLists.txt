cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico-projects)

pico_sdk_init()

add_executable(tally_light
    tally_light.c
)

target_link_libraries(tally_light pico_stdlib)

pico_enable_stdio_uart(tally_light 0)
pico_enable_stdio_usb(tally_light 1)

pico_add_extra_outputs(tally_light)