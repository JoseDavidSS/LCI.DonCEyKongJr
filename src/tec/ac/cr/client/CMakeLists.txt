cmake_minimum_required(VERSION 3.14)
project(DonceyKongJr)

set(CMAKE_C_STANDARD 99)

add_executable(DonceyKongJr src/main.c src/gui.c src/gui.h src/bitmapNode.c src/bitmapNode.h)
target_link_libraries(DonceyKongJr -lmingw32 -lallegro-5.0.10-monolith-md-debug)




