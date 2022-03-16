//
// Created by Xander on 2022/3/12.
//

#include "BST.h"

// FIXME: duplicate key issue
BST::BSTNode::BSTNode(int key) {
    this->key = key;
    this->right = nullptr;
    this->left = nullptr;
}

BST::BST() {
    this->root = nullptr;
}

void BST::Insert(int key) {
    this->root = Insert(this->root, key);
}

void BST::Delete(int key) {
    this->root = Delete(this->root, key);
}

bool BST::Query(int key) {
    return Query(this->root, key);
}

bool BST::Query(BSTNode *node, int key) {
    if (node == nullptr) return false;
    int thisKey = node->key;
    if (thisKey == key) {
        return true;
    } else if (thisKey > key) {
        return Query(node->left, key);
    } else {
        return Query(node->right, key);
    }
}
// TODO: free the memory after deletion
BST::BSTNode *BST::Delete(BST::BSTNode *node, int key) {
    if (node == nullptr) return nullptr;
    if (node->key == key) {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left != nullptr && node->right != nullptr) {
            int newKey = FindMinValue(node->right);
            node->key = newKey;
            node->right = Delete(node->right, newKey);
            return node;
        } else if (node->left != nullptr) {
            BSTNode *ret = node->left;
            delete node;
            return ret;
        } else {
            BSTNode *ret = node->right;
            delete node;
            return ret;
        }
    } else if (node->key < key) {
        node->right = Delete(node->right, key);
    } else {
        node->left = Delete(node->left, key);
    }
    return node;
}

BST::BSTNode *BST::Insert(BST::BSTNode *node, int key) {
    if (node == nullptr) {
        return new BSTNode(key);
    }
    if (node->key < key) {
        node->right = Insert(node->right, key);
    } else {
        node->left = Insert(node->left, key);
    }
    return node;
}

int BST::FindMinValue(BST::BSTNode *node) {
    BST::BSTNode *ptr = node;
    while (ptr->left != nullptr) {
        ptr = ptr->left;
    }
    return ptr->key;
}
