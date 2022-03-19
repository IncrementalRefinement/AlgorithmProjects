cmake_minimum_required(VERSION 3.21)
project(Proj1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BST_test
        BST/BST.cpp
        BST/BST.h
        BST/BST_test.cpp
        )

add_executable(AvlTree_test
        AvlTree/AvlTree.cpp
        AvlTree/AvlTree.h
        AvlTree/AvlTreeTest.cpp
        )

add_executable(RBT_Test
        RBT/RBT.h
        RBT/RBT.cpp
        RBT/RBT_Test.cpp
        )

add_executable(SplayTree_Test
        SplayTree/splayTree.h
        SplayTree/splayTree.cpp
        )