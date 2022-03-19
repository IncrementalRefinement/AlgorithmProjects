cmake_minimum_required(VERSION 3.21)
project(splayTree_src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(splayTree_src
        splayTree.cpp
        splayTree.h)
