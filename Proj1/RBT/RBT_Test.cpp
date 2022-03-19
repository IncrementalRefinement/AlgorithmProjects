#include <iostream>
#include <cassert>

#include "RBT.h"

void sanityTest() {
    RBT theTree = RBT_initTree();
    for (int i = 0; i < 1000; i++) {
        RBT_Insert(theTree, i);
    }

    for (int i = 0; i < 1000; i++) {
        assert(RBT_Query(theTree, i));
    }

    for (int i = 0; i < 1000; i++) {
        RBT_Delete(theTree, i);
    }

    for (int i = 0; i < 1000; i++) {
        assert(RBT_Query(theTree, i) == NULL);
    }

    std::cout << "Passed sanity test" << std::endl;
}

int main() {
    sanityTest();
}
