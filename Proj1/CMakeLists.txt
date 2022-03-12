cmake_minimum_required(VERSION 3.21)
project(Proj1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Proj1
        BST.cpp
        BST.h
        BST_test.cpp
        )
