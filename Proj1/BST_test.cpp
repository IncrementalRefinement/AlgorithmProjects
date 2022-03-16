//
// Created by Xander on 2022/3/12.
//

#include <iostream>
#include <algorithm>
#include <cassert>
#include <array>
#include <random>
#include <chrono>

#include "BST.h"

void testSanity() {
    BST *theTree = new BST();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
    }

    for (int i = 0; i < 10; i++) {
        assert(theTree->Query(i));
    }

    for (int i = 0; i < 10; i++) {
        theTree->Delete(i);
    }

    for (int i = 0; i < 10; i++) {
        assert(!theTree->Query(i));
    }
}

void testInsert() {
    BST *theTree = new BST();
    for (int i = 11; i < 20; i++) {
        theTree->Insert(i);
    }
}

void testQuery()  {
    BST *theTree = new BST();
    for (int i = 11; i < 20; i++) {
        theTree->Insert(i);
    }

    for (int i = 11; i < 20; i++) {
        assert(theTree->Query(i));
    }
}

void testDelete() {
    BST *theTree = new BST();
    for (int i = 11; i < 20; i++) {
        theTree->Insert(i);
    }

    for (int i = 11; i < 20; i++) {
        theTree->Delete(i);
    }

    for (int i = 11; i < 20; i++) {
        assert(!theTree->Query(i));
    }
}

void specialFail() {
    auto *theTree = new BST();
    int insertOrder[10] = {0, 5, 2, 7, 9, 3, 8, 1, 4, 6};
    int deleteOrder[10] = {2, 8, 4, 6, 3, 1, 5, 7, 0, 9};

    for (int item : insertOrder) {
        theTree->Insert(item);
        assert(theTree->Query(item));
    }

    for (int item :deleteOrder) {
        theTree->Delete(item);
        assert(!theTree->Query(item));
    }
 }

void RandomInsertDeleteTest() {
    auto *theTree = new BST();
    std::vector<int> checkArray;
    checkArray.resize(10000);
    for (int i = 0; i < 10000; i++) {
        checkArray[i] = i;
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(checkArray.begin(), checkArray.end(), std::default_random_engine(seed));

    for (int i = 0; i < 10000; i++) {
        theTree->Insert(checkArray[i]);
        assert(theTree->Query(checkArray[i]));
    }

    unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(checkArray.begin(), checkArray.end(), std::default_random_engine(seed2));

    for (int i = 0; i < 10000; i++) {
        theTree->Delete(checkArray[i]);
        assert(!(theTree->Query(checkArray[i])));
    }

    std::cout << "RandomInsertDeleteTest passed" << std::endl;
}

int main() {
    testSanity();
    std::cout << "Passed " << "testSanity" << std::endl;
    testInsert();
    std::cout << "Passed " << "testInsert" << std::endl;
    testQuery();
    std::cout << "Passed " << "testQuery" << std::endl;
    testDelete();
    std::cout << "Passed " << "testDelete" << std::endl;
    specialFail();
    RandomInsertDeleteTest();
}