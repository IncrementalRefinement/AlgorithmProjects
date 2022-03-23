//
// Created by Xander on 2022/3/23.
//

#include "RedBlackTree.h"

const int TYPE_RED = 0;
const int TYPE_BLACK = 1;
const int TYPE_DOUBLE_BLACK = 2;

RedBlackTree::RedBlackTree() {
    root = nullptr;
}

void RedBlackTree::checkRep() {
    return;
}

void RedBlackTree::Insert(int key) {
    // 1. find the place to insert
    // 2. insert
    // 3. handle double red
}

bool RedBlackTree::Query(int key) {
    return findNode(key) != nullptr;
}

void RedBlackTree::Delete(int key) {
    // 1. find the place to delete
    // 2. delete and mark the double black if necessary
    // 3. handle double black node
}

RedBlackTree::Node *RedBlackTree::findNode(int key) {
    Node *ptr = root;
    while (ptr != nullptr) {
        if (key == ptr->key) {
            break;
        } else if (key > ptr->key) {
            ptr = ptr->rightChild;
        } else {
            ptr = ptr->leftChild;
        }
    }
    return ptr;
}


RedBlackTree::Node *RedBlackTree::leftRotate(RedBlackTree::Node *node) {
    return nullptr;
}

RedBlackTree::Node *RedBlackTree::rightRotate(RedBlackTree::Node *node) {
    return nullptr;
}

// The child of the input node is red, and the node is also red
void RedBlackTree::handleDoubleRed(RedBlackTree::Node *node) {

}

// The node is double black. Also, although the node might have value, it might be double black NIL node
void RedBlackTree::handleDoubleBlack(RedBlackTree::Node *node) {

}

RedBlackTree::Node *RedBlackTree::Node::getSibling() {
    return nullptr;
}
