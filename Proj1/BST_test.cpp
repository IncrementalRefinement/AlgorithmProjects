//
// Created by Xander on 2022/3/12.
//

#include <iostream>
#include <cassert>
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

int main() {
    testSanity();
    std::cout << "Passed " << "testSanity" << std::endl;
    testInsert();
    std::cout << "Passed " << "testInsert" << std::endl;
    testQuery();
    std::cout << "Passed " << "testQuery" << std::endl;
    testDelete();
    std::cout << "Passed " << "testDelete" << std::endl;
}