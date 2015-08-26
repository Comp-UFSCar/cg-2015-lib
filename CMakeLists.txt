cmake_minimum_required(VERSION 2.8cmake)
project(monitor_cthulhu)

set(SOURCE_FILES
        lib/functions_lib.h
        src/monitor_cthulhu.c
        lib/structs_lib.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(monitor_cthulhu ${SOURCE_FILES})
target_link_libraries(monitor_cthulhu m X11)