
cmake_minimum_required(VERSION 3.16)
project(4c04)

set(CMAKE_C_STANDARD 11)

ADD_DEFINITIONS(-Wall -Wextra -Wconversion -pedantic -c -g -O0 -std=gnu99)

find_package(X11 REQUIRED)

message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

include_directories(${X11_INCLUDE_DIR})

add_executable(4c04 lib/eOOPc.h 4c04.c cpu_class.c lib/cpu_pub.h window_class.c lib/window_pub.h debug_class.c lib/debug_pub.h strings_class.c lib/strings_pub.h program_class.c lib/program_pub.h lib/window_class.h lib/common.h lib/cpu_class.h draw_class.c lib/draw_class.h lib/draw_pub.h)

target_link_libraries(4c04 X11)