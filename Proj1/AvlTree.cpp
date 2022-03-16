//
// Created by Xander on 2022/3/15.
//

#include <cstdlib>
#include <cassert>
#include <algorithm>

#include "AvlTree.h"

AvlTree::AvlTreeNode::AvlTreeNode(int key) {
    this->key = key;
    this->left = nullptr;
    this->right = nullptr;
    this->leftDepth = 0;
    this->rightDepth = 0;
}

AvlTree::AvlTree() {
    this->root = nullptr;
}

void AvlTree::Delete(int key) {
    this->root = Delete(root, key);
}

void AvlTree::Insert(int key) {
    this->root = Insert(root, key);
}

bool AvlTree::Query(int key) {
    return Query(root, key);
}

bool AvlTree::Query(AvlTree::AvlTreeNode *node, int key) {
    if (node == nullptr) return false;
    if (key == node->key) {
        return true;
    } else if (key > node->key) {
        return Query(node->right, key);
    } else {
        return Query(node->left, key);
    }
}


AvlTree::AvlTreeNode *AvlTree::Delete(AvlTree::AvlTreeNode *node, int key) {
    if (node->key == key) {
        if (node->left == nullptr && node->right == nullptr) {
            return nullptr;
        } else if (node->left != nullptr && node->right != nullptr) {
            int newKey = FindMinValue(node->right);
            node->key = newKey;
            node->right = Delete(node->right, newKey);
        } else if (node->left != nullptr) {
            node = node->left;
        } else {
            node = node->right;
        }
    } else if (key < node->key) {
        node->left = Delete(node->left, key);
    } else {
        node->right = Delete(node->right, key);
    }
    updateHeight(node);
    return rotateIfNecessary(node);
}

AvlTree::AvlTreeNode *AvlTree::Insert(AvlTree::AvlTreeNode *node, int key) {
    if (node == nullptr) {
        node = new AvlTreeNode(key);
    } else if (node->key < key) {
        node->right = Insert(node->right, key);
    } else {
        node->left = Insert(node->left, key);
    }
    updateHeight(node);
    return rotateIfNecessary(node);
}

int AvlTree::FindMinValue(AvlTree::AvlTreeNode *node) {
    AvlTree::AvlTreeNode *ptr = node;
    while (ptr->left != nullptr) {
        ptr = ptr->left;
    }
    return ptr->key;
}

AvlTree::AvlTreeNode *AvlTree::rotateIfNecessary(AvlTree::AvlTreeNode *node) {
    if (isUnbalance(node)) {
        if (node->leftDepth > node->rightDepth) {
            if (node->left->leftDepth < node->left->rightDepth) {
                node->left = leftRotate(node->left);
            }
            node = rightRotate(node);
        } else {
            if (node->right->leftDepth > node->right->rightDepth) {
                node->right = rightRotate(node->right);
            }
            node = leftRotate(node);
        }
    }
    return node;
}

AvlTree::AvlTreeNode *AvlTree::leftRotate(AvlTree::AvlTreeNode *node) {
    AvlTreeNode *v = node->right;
    node->right = v->left;
    v->left = node;
    updateHeight(node);
    updateHeight(v);
    return v;
}

AvlTree::AvlTreeNode *AvlTree::rightRotate(AvlTree::AvlTreeNode *node) {
   AvlTreeNode *v = node->left;
   node->left = v->right;
   v->right = node;
    updateHeight(node);
    updateHeight(v);
   return v;
}

void AvlTree::checkRep() {
    checkRep(root);
}

void AvlTree::checkRep(AvlTree::AvlTreeNode *node) {
    if (node == nullptr) return;
    assert(abs(node->leftDepth - node->rightDepth) <= 1);
    checkRep(node->left);
    checkRep(node->right);
}

void AvlTree::updateHeight(AvlTree::AvlTreeNode *node) {
    if (node->right == nullptr) {
        node->rightDepth = 0;
    } else {
        node->rightDepth = getHeight(node->right) + 1;
    }

    if (node->left == nullptr) {
        node->leftDepth = 0;
    } else {
        node->leftDepth = getHeight(node->left) + 1;
    }
}

int AvlTree::getHeight(AvlTree::AvlTreeNode *node) {
    // node is not null
    return std::max(node->leftDepth, node->rightDepth);
}

bool AvlTree::isUnbalance(AvlTreeNode *node) {
    return abs(node->leftDepth - node->rightDepth) > 1;
}
