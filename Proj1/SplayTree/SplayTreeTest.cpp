//
// Created by Xander on 2022/3/22.
//

#include <iostream>
#include <algorithm>
#include <cassert>
#include <random>
#include <chrono>

#include "splayTree.h"

void SanityTest() {
    auto *theTree = new SplayTree();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
    }

    for (int i = 0; i < 10; i++) {
        theTree->Query(i);
    }

    for (int i = 0; i < 10; i++) {
        theTree->Delete(i);
    }
    std::cout << "SanityTest passed" << std::endl;
}

void InsertTest() {
    auto *theTree = new SplayTree();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
    }

    std::cout << "InsertTest passed" << std::endl;
}

void QueryTest() {
    auto *theTree = new SplayTree();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
    }

    for (int i = 0; i < 10; i++) {
        assert(theTree->Query(i));
    }

    std::cout << "QueryTest passed" << std::endl;
}

void DeleteTest() {
    auto *theTree = new SplayTree();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
    }

    for (int i = 0; i < 10; i++) {
        theTree->Delete(i);
        assert(!theTree->Query(i));
    }

    std::cout << "DeleteTest passed" << std::endl;
}

void RandomInsertDeleteTest() {
    auto *theTree = new SplayTree();
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

    seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(checkArray.begin(), checkArray.end(), std::default_random_engine(seed));
    for (int i = 0; i < 10000; i++) {
        theTree->Delete(checkArray[i]);
        assert(!theTree->Query(checkArray[i]));
    }

    std::cout << "RandomInsertDeleteTest passed" << std::endl;
}

int main() {
    SanityTest();
    InsertTest();
    QueryTest();
    DeleteTest();
    RandomInsertDeleteTest();
}
