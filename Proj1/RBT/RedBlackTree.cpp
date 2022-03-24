//
// Created by Xander on 2022/3/23.
//

#include <cassert>

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

// TODO: 笔记上的插入之后的旋转针对的是 u 是左子节点的情况，我想如果u是右子节点，这里额外做一次旋转来解决这个问题(当然也可以在handle double red 里面做)
void RedBlackTree::Insert(int key) {
    // 1. find the place to insert
    Node *prev = nullptr;
    Node *ptr = root;
    while (ptr != nullptr) {
        prev = ptr;
        if (key > ptr->key) {
            ptr = ptr -> rightChild;
        } else {
            ptr = ptr->leftChild;
        }
    }
    // 2. insert
    if (prev == nullptr) {
        // the tree is empty
        root = new Node(key);
        root->type = TYPE_BLACK;
    } else {
        Node *newNode = new Node(key);
        newNode->parent = prev;
        if (key > prev->key) {
            prev->rightChild = newNode;
        } else {
            prev->leftChild = newNode;
        }
    }
    // 3. handle double red
    if (prev != nullptr && prev->type == TYPE_RED) {
        handleDoubleRed(prev);
    }
}


void RedBlackTree::Delete(int key) {
    Delete(key, nullptr);
}

bool RedBlackTree::Query(int key) {
    return findNode(key) != nullptr;
}

void RedBlackTree::Delete(int key, Node *theNode) {
    Node *nodeToDelete = nullptr;
    // 1. find the place to delete
    if (theNode == nullptr) {
        Node *foundNode = findNode(key);
        if (foundNode->leftChild != nullptr && foundNode->rightChild != nullptr) {
            nodeToDelete = findMin(foundNode->rightChild);
            int temp = nodeToDelete->key;
            nodeToDelete->key = foundNode->key;
            foundNode->key = temp;
            Delete(-1, nodeToDelete);
        } else {
            nodeToDelete = foundNode;
        }
    } else {
        nodeToDelete = theNode;
    }

    // 2. delete and mark the double black if necessary
    // the node will only have one child here
    assert(!(nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild != nullptr));
    if (nodeToDelete->type == TYPE_RED) {
        // if the node is red, simply delete the node
    } else {
        if (nodeToDelete->leftChild != nullptr) {
            // the left child is red
            nodeToDelete->key = nodeToDelete->leftChild->key;
            DeleteLeafNode(nodeToDelete->leftChild);
        } else if (nodeToDelete->rightChild != nullptr) {
            // the right child is red
            nodeToDelete->key = nodeToDelete->rightChild->key;
            DeleteLeafNode(nodeToDelete->rightChild);
        } else {
            // the node has two nil(black) child
            nodeToDelete->type = TYPE_DOUBLE_BLACK;
            // 3. handle double black node
            handleDoubleRed(nodeToDelete);
        }
    }

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
    Node *theParent = node->parent;
    Node *u = node;
    Node *v = u->rightChild;
    assert(u != nullptr && v != nullptr);
    Node *A = u->leftChild;
    Node *B = v->leftChild;
    Node *C = v->rightChild;

    u->rightChild = B;
    if (B != nullptr) {
        B->parent = u;
    }
    v->leftChild = u;
    u->parent = v;
    v->parent = theParent;
    if (theParent != nullptr) {
        if (u == theParent->leftChild) {
            v = theParent->leftChild;
        } else {
            v = theParent->rightChild;
        }
    } else {
        // the node is the root
        root = v;
    }
}

RedBlackTree::Node *RedBlackTree::rightRotate(RedBlackTree::Node *node) {
    Node *theParent = node->parent;
    Node *v = node;
    Node *u = v->leftChild;
    assert(u != nullptr && v != nullptr);
    Node *A = u->leftChild;
    Node *B = u->rightChild;
    Node *C = v->rightChild;

    v->leftChild = B;
    if (B != nullptr) {
        B->parent = v;
    }
    u->rightChild = v;
    v->parent = u;
    u->parent = theParent;
    if (theParent != nullptr) {
        if (v == theParent->leftChild) {
            u = theParent->leftChild;
        } else {
            u = theParent->rightChild;
        }
    } else {
        // the node is the root
        root = u;
    }
}

// The child of the input node is red, and the node is also red
void RedBlackTree::handleDoubleRed(RedBlackTree::Node *node) {
    // TODO
}

// The node is double black. Also, although the node might have value, it might be double black NIL node
void RedBlackTree::handleDoubleBlack(RedBlackTree::Node *node) {
    // TODO
}

RedBlackTree::Node *RedBlackTree::findMin(RedBlackTree::Node *node) {
    while (node->leftChild != nullptr) {
        node = node->leftChild;
    }
    return node;
}


void RedBlackTree::DeleteLeafNode(RedBlackTree::Node *theNode) {
    if (theNode->parent == nullptr) {
        // root node
        assert(theNode == root && root->leftChild == nullptr && root->rightChild == nullptr);
        delete theNode;
        root = nullptr;
    } else {
        if (theNode->parent->leftChild == theNode) {
            theNode->parent->leftChild = nullptr;
        } else {
            theNode->parent->rightChild = nullptr;
        }
        delete theNode;
    }
}

RedBlackTree::Node *RedBlackTree::Node::getSibling() {
    assert(this->parent != nullptr);

    if (this->parent->leftChild == this) {
        return this->parent->rightChild;
    } else {
        return this->parent->leftChild;
    }
}

RedBlackTree::Node::Node(int key) {
        this->key = key;
        this->type = TYPE_RED;
        this->parent = nullptr;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
}
