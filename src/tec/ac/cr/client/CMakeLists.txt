cmake_minimum_required(VERSION 3.14)
project(DonceyKongJr)

set(CMAKE_C_STANDARD 99)

add_executable(DonceyKongJr src/main.c src/gui.c src/gui.h src/bitmapNode.c src/bitmapNode.h src/logic/entity/DKJr.h src/logic/entity/Fruit.h src/logic/entity/Kremlin.h src/logic/Game.c src/logic/Game.h src/logic/lists/FruitNode.c src/logic/lists/FruitNode.h src/logic/lists/KremlinNode.c src/logic/lists/KremlinNode.h)
target_link_libraries(DonceyKongJr -lmingw32 -lallegro-5.0.10-monolith-md-debug)




