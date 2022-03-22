//
// Created by 12638 on 2022/3/20.
//

#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H
// Implementing Red-Black Tree in C++
#include <string>
#include <iostream>

using namespace std;
struct Node {
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color;
};

typedef Node *NodePtr;

class RedBlackTree {
private:
    NodePtr root;
    NodePtr TNULL;

    NodePtr searchTreeHelper(NodePtr node, int key);

    // For balancing the tree after deletion
    void deleteFix(NodePtr x);

    void rbTransplant(NodePtr u, NodePtr v);

    // For balancing the tree after insertion
    void insertFix(NodePtr k);

public:
    RedBlackTree();

    NodePtr Query(int k);

    void leftRotate(NodePtr x);

    void rightRotate(NodePtr x);

    // Inserting a node
    void Insert(int key);

    void Delete(int data);

    NodePtr minimum(NodePtr node);
};

#endif //REDBLACKTREE_REDBLACKTREE_H
