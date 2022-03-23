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
add_executable(RedBlackTreeTest
        RBT/RedBlackTree.h
        RBT/RedBlackTree.cpp
        RBT/RedBlackTreeTest.cpp
        )
add_executable(SplayTree_Test
        SplayTree/splayTree.h
        SplayTree/splayTree.cpp
        SplayTree/SplayTreeTest.cpp
        )

add_executable(OverallTest
        BST/BST.h
        BST/BST.cpp
        AvlTree/AvlTree.h
        AvlTree/AvlTree.cpp
        SplayTree/splayTree.h
        SplayTree/splayTree.cpp
        RBT/RedBlackTree.h
        RBT/RedBlackTree.cpp
        OverallTest.cpp
        )
