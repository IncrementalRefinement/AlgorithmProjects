//
// Created by Xander on 2022/3/15.
//

#include <iostream>
#include <cassert>

#include "AvlTree.h"

void SanityTest() {
    auto *theTree = new AvlTree();
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
    auto *theTree = new AvlTree();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
    }

    theTree->checkRep();
    std::cout << "InsertTest passed" << std::endl;
}

void QueryTest() {
    auto *theTree = new AvlTree();
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
    auto *theTree = new AvlTree();
    for (int i = 0; i < 10; i++) {
        theTree->Insert(i);
    }
    theTree->checkRep();
    for (int i = 0; i < 10; i++) {
        theTree->Delete(i);
    }
    theTree->checkRep();
    for (int i = 0; i < 10; i++) {
        assert(!theTree->Query(i));
    }
    theTree->checkRep();
    std::cout << "DeleteTest passed" << std::endl;
}

int main() {
    SanityTest();
    InsertTest();
    QueryTest();
    DeleteTest();
}
