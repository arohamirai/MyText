cmake_minimum_required(VERSION 2.8)
project(broadcast)

set( CMAKE_BUILD_TYPE Release )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )
#add_definitions(-std=c++11 -O2 -g -DNDEBUG)


add_executable(broadcast_server src/broadcast_server.c)
add_executable(broadcast_client src/broadcast_client.c)
