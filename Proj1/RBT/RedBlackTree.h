//
// Created by 12638 on 2022/3/20.
//

#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H
// Implementing Red-Black Tree in C++
#include <string>
#include <iostream>

using namespace std;
struct RBTnode {
    int data;
    RBTnode *parent;
    RBTnode *left;
    RBTnode *right;
    int color;
};

typedef RBTnode *RBTnodePtr;

class RedBlackTree {
private:
    RBTnodePtr root;
    RBTnodePtr TNULL;

    RBTnodePtr searchTreeHelper(RBTnodePtr node, int key);

    // For balancing the tree after deletion
    void deleteFix(RBTnodePtr x);

    void rbTransplant(RBTnodePtr u, RBTnodePtr v);

    // For balancing the tree after insertion
    void insertFix(RBTnodePtr k);

public:
    RedBlackTree();

    RBTnodePtr Query(int k);

    void leftRotate(RBTnodePtr x);

    void rightRotate(RBTnodePtr x);

    // Inserting a node
    void Insert(int key);

    void Delete(int data);

    RBTnodePtr minimum(RBTnodePtr node);
};

#endif //REDBLACKTREE_REDBLACKTREE_H
