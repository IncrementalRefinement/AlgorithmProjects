//
// Created by 12638 on 2022/3/20.
//

#ifndef SPLAYTREE_SRC_REDBLACKTREE_H
#define SPLAYTREE_SRC_REDBLACKTREE_H
// Implementing Red-Black Tree in C++
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

    void initializeNULLNode(NodePtr node, NodePtr parent) {}

    // Post order
    void postOrderHelper(NodePtr node) {}

    NodePtr searchTreeHelper(NodePtr node, int key) {}

    // For balancing the tree after deletion
    void deleteFix(NodePtr x) {}

    void rbTransplant(NodePtr u, NodePtr v) {
    }

    void deleteNodeHelper(NodePtr node, int key) {
    }

    // For balancing the tree after insertion
    void insertFix(NodePtr k) {}

    void printHelper(NodePtr root, string indent, bool last) {
    }

public:
    RedBlackTree() {
    }

    NodePtr searchTree(int k) {}


    NodePtr successor(NodePtr x) {}

    NodePtr predecessor(NodePtr x) {}

    void leftRotate(NodePtr x) {
    }

    void rightRotate(NodePtr x) {
    }

    // Inserting a node
    void insert(int key) {
    }

    NodePtr getRoot() {
    }

    void deleteNode(int data) {
    }

    void printTree() {
    }
};

#endif //SPLAYTREE_SRC_REDBLACKTREE_H
