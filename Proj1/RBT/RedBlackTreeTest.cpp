
#include <iostream>
#include <algorithm>
#include <cassert>
#include <random>
#include <chrono>

#include "RedBlackTree.h"

void SanityTest() {
    auto *theTree = new RedBlackTree();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
    }
    theTree->checkRep();
    for (int i = 0; i < 10; i++) {
        theTree->Query(i);
    }
    theTree->checkRep();

    for (int i = 0; i < 10; i++) {
        theTree->Delete(i);
    }
    theTree->checkRep();

    std::cout << "SanityTest passed" << std::endl;
}

void InsertTest() {
    auto *theTree = new RedBlackTree();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
    }
    theTree->checkRep();
    std::cout << "InsertTest passed" << std::endl;
}

void QueryTest() {
    auto *theTree = new RedBlackTree();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
    }
    theTree->checkRep();

    for (int i = 0; i < 10; i++) {
        assert(theTree->Query(i));
    }
    theTree->checkRep();

    std::cout << "QueryTest passed" << std::endl;
}

void DeleteTest() {
    auto *theTree = new RedBlackTree();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
        assert(theTree->Query(i));
    }
    theTree->checkRep();

    for (int i = 0; i < 10; i++) {
        theTree->Delete(i);
        assert(!theTree->Query(i));
    }
    theTree->checkRep();

    std::cout << "DeleteTest passed" << std::endl;
}


void SpecialTest() {
    auto *theTree = new RedBlackTree();
    int count = 5;
    int checkArray[5] = {4, 1, 2, 3,0};

    for (int i = 0; i < 5; i++) {
        theTree->Insert(checkArray[i]);
        assert(theTree->Query(checkArray[i]));
        theTree->checkRep();
    }

    for (int i = 0; i < 5; i++) {
        theTree->Delete(checkArray[i]);
        assert(!theTree->Query(checkArray[i]));
        theTree->checkRep();
    }

    std::cout << "SpecialTest passed" << std::endl;
}

void RandomInsertDeleteTest() {
    auto *theTree = new RedBlackTree();
    std::vector<int> checkArray;
    int count = 10000;
    checkArray.resize(count);
    for (int i = 0; i < count; i++) {
        checkArray[i] = i;
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(checkArray.begin(), checkArray.end(), std::default_random_engine(seed));

    for (int i = 0; i < count; i++) {
        theTree->Insert(checkArray[i]);
        assert(theTree->Query(checkArray[i]));
        theTree->checkRep();
    }

     seed = std::chrono::system_clock::now().time_since_epoch().count();
     std::shuffle(checkArray.begin(), checkArray.end(), std::default_random_engine(seed));
    for (int i = 0; i < count; i++) {
        theTree->Delete(checkArray[i]);
        assert(!theTree->Query(checkArray[i]));
        theTree->checkRep();
    }

    std::cout << "RandomInsertDeleteTest passed" << std::endl;
}

int main() {
    SanityTest();
    InsertTest();
    QueryTest();
    DeleteTest();
    SpecialTest();
    RandomInsertDeleteTest();
}
