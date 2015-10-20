cmake_minimum_required(VERSION 2.8cmake)
project(monitor_cthulhu)

set(SOURCE_FILES
        header/base_functions.h
        src/monitor_cthulhu.c
        header/structs.h
        header/monitor_cthulhu.h
        src/base_functions.c
        src/object2d_functions.c
        header/object2d_functions.h)

set(LIBS m X11)

set(CMAKE_C_FLAGS "-std=c99")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(monitor_cthulhu ${SOURCE_FILES})
target_link_libraries(monitor_cthulhu ${LIBS})
