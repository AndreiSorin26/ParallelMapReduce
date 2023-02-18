cmake_minimum_required(VERSION 3.24)
project(MapReduce)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MapReduce
        main.cpp
        map_reduce.cpp
        map_reduce.h
        mapper.cpp
        mapper.h
        reducer.cpp
        reducer.h
        workpool.cpp
        workpool.h)
