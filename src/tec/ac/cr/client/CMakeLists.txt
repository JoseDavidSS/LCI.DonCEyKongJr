cmake_minimum_required(VERSION 3.14)
project(DonceyKongJr)

set(CMAKE_C_STANDARD 99)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
ADD_COMPILE_OPTIONS(${GTK3_CFLAGS_OTHER})
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})
set(LIBRARIES ${LIBRARIES} ${GTK3_LIBRARIES})

set(FLAGS "-I${GTK3_INCLUDE_DIRS}")
message(STATUS "Flags: ${FLAGS}")
string(REPLACE ";" " -I" FLAGS "${FLAGS}")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${GTK3_FLAGS} ${FLAGS})

add_executable(DonceyKongJr src/main.c src/ui/AllegroWindow.c src/ui/gui.c src/ui/gui.h src/logic/entity/DKJr.h src/logic/entity/Fruit.h src/logic/entity/Kremlin.h src/logic/Game.c src/logic/Game.h src/logic/lists/FruitNode.c src/logic/lists/FruitNode.h src/logic/lists/KremlinNode.c src/logic/lists/KremlinNode.h src/socket/Socket.c src/socket/Socket.h src/ui/AllegroWindow.h src/socket/Serializer.c src/socket/Serializer.h src/socket/cJson.c src/socket/cJson.h)
target_link_libraries(DonceyKongJr -lmingw32 -lallegro-5.0.10-monolith-md-debug ${GTK3_LIBRARIES} wsock32 ws2_32)




