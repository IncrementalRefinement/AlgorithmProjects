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

int RedBlackTree::checkRep(RedBlackTree::Node *node) {
    if (node == nullptr) {
        return 1;
    }

    assert(node->type == TYPE_BLACK || node->type == TYPE_RED);
    int leftDepth = checkRep(node->leftChild);
    int rightDepth = checkRep(node->rightChild);

    assert(leftDepth == rightDepth);

    if (node->type == TYPE_RED) {
        assert(node->leftChild == nullptr || node->leftChild->type != TYPE_RED);
        assert(node->rightChild == nullptr || node->rightChild->type != TYPE_RED);
    }

    if (node->type == TYPE_BLACK) {
        return leftDepth + 1;
    } else {
        return leftDepth;
    }
}

void RedBlackTree::checkRep() {
    assert(root == nullptr || root->type == TYPE_BLACK);
    checkRep(root);
}

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
            return;
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
        DeleteLeafNode(nodeToDelete);
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
            if (nodeToDelete != root) {
                handleDoubleBlack(nodeToDelete);
            }
            DeleteLeafNode(nodeToDelete);
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
            theParent->leftChild = v;
        } else {
            theParent->rightChild = v;
        }
    } else {
        // the node is the root
        root = v;
    }

    return v;
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
            theParent->leftChild = u;
        } else {
            theParent->rightChild = u;
        }
    } else {
        // the node is the root
        root = u;
    }

    return u;
}

// The child of the input node is red, and the node is also red
void RedBlackTree::handleDoubleRed(RedBlackTree::Node *node) {
    if (node->parent != nullptr && node == node->parent->rightChild) {
        handleDoubleRedOnRight(node);
    } else {
        handleDoubleRedOnLeft(node);
    }
}

void RedBlackTree::handleDoubleRedOnLeft(RedBlackTree::Node *node) {
    bool isLeftChildRed = false;
    Node *parentNode = node->parent;
    Node *siblingNode = node->getSibling();
    Node *v = nullptr;

    if (node->leftChild != nullptr && node->leftChild->type == TYPE_RED) {
        isLeftChildRed = true;
        v = node->leftChild;
    } else {
        isLeftChildRed = false;
        v = node->rightChild;
    }

    if (siblingNode != nullptr && siblingNode->type == TYPE_RED) {
        // case 1
        node->type = TYPE_BLACK;
        siblingNode->type = TYPE_BLACK;
        parentNode->type = TYPE_RED;
        if (parentNode == root) {
            parentNode->type = TYPE_BLACK;
        } else if (parentNode->parent->type == TYPE_BLACK) {
            return;
        } else {
            handleDoubleRed(parentNode->parent);
        }
    } else {
        // case 2
        if (node->leftChild == v) {
            // case 2.1
            node->type = TYPE_BLACK;
            parentNode->type = TYPE_RED;
            rightRotate(parentNode);
        } else {
            // case 2.2
            leftRotate(node);
            handleDoubleRed(v);
        }
    }
}

void RedBlackTree::handleDoubleRedOnRight(RedBlackTree::Node *node) {
    bool isLeftChildRed = false;
    Node *parentNode = node->parent;
    Node *siblingNode = node->getSibling();
    Node *v = nullptr;

    if (node->leftChild != nullptr && node->leftChild->type == TYPE_RED) {
        isLeftChildRed = true;
        v = node->leftChild;
    } else {
        isLeftChildRed = false;
        v = node->rightChild;
    }

    if (siblingNode != nullptr && siblingNode->type == TYPE_RED) {
        // case 1
        node->type = TYPE_BLACK;
        siblingNode->type = TYPE_BLACK;
        parentNode->type = TYPE_RED;
        if (parentNode == root) {
            parentNode->type = TYPE_BLACK;
        } else if (parentNode->parent->type == TYPE_BLACK) {
            return;
        } else {
            handleDoubleRed(parentNode->parent);
        }
    } else {
        // case 2
        if (node->rightChild == v) {
            // case 2.1
            node->type = TYPE_BLACK;
            parentNode->type = TYPE_RED;
            leftRotate(parentNode);
        } else {
            // case 2.2
            rightRotate(node);
            handleDoubleRed(v);
        }
    }
}


// The node is double black. Also, although the node might have value, it might be double black NIL node
void RedBlackTree::handleDoubleBlack(RedBlackTree::Node *node) {
    if (node->parent != nullptr && node == node->parent->leftChild) {
        handleDoubleBlackLeft(node);
    } else {
        handleDoubleBlackRight(node);
    }
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

void RedBlackTree::handleDoubleBlackLeft(RedBlackTree::Node *node) {
    Node *parentNode = node->parent;
    Node *siblingNode = node->getSibling();

    if (siblingNode == nullptr || siblingNode->type == TYPE_BLACK) {
        // case 1
        if ((siblingNode->leftChild == nullptr || siblingNode->leftChild->type == TYPE_BLACK)
        && (siblingNode->rightChild == nullptr || siblingNode->rightChild->type == TYPE_BLACK)) {
            // case 1.1
            node->type = TYPE_BLACK;
            siblingNode->type = TYPE_RED;
            if (parentNode->type == TYPE_RED) {
                parentNode->type = TYPE_BLACK;
            } else {
                if (parentNode == root) {
                    parentNode->type = TYPE_BLACK;
                } else {
                    parentNode->type = TYPE_DOUBLE_BLACK;
                    handleDoubleBlack(parentNode);
                }
            }
        } else if (siblingNode->rightChild != nullptr && siblingNode->rightChild->type == TYPE_RED) {
            // case 1.2
            node->type = TYPE_BLACK;
            siblingNode->rightChild->type = TYPE_BLACK;
            siblingNode->type = parentNode->type;
            parentNode->type = TYPE_BLACK;
            leftRotate(parentNode);
        } else {
            // case 1.3
            node->type = TYPE_BLACK;
            siblingNode->leftChild->type = parentNode->type;
            parentNode->type = TYPE_BLACK;
            rightRotate(siblingNode);
            leftRotate(parentNode);
        }
    } else {
        // case 2
        parentNode->type = TYPE_RED;
        siblingNode->type = TYPE_BLACK;
        leftRotate(parentNode);
        handleDoubleBlack(node);
    }
}

void RedBlackTree::handleDoubleBlackRight(RedBlackTree::Node *node) {

    Node *parentNode = node->parent;
    Node *siblingNode = node->getSibling();

    if (siblingNode == nullptr || siblingNode->type == TYPE_BLACK) {
        // case 1
        if ((siblingNode->leftChild == nullptr || siblingNode->leftChild->type == TYPE_BLACK)
            && (siblingNode->rightChild == nullptr || siblingNode->rightChild->type == TYPE_BLACK)) {
            // case 1.1
            node->type = TYPE_BLACK;
            siblingNode->type = TYPE_RED;
            if (parentNode->type == TYPE_RED) {
                parentNode->type = TYPE_BLACK;
            } else {
                if (parentNode == root) {
                    parentNode->type = TYPE_BLACK;
                } else {
                    parentNode->type = TYPE_DOUBLE_BLACK;
                    handleDoubleBlack(parentNode);
                }
            }
        } else if (siblingNode->leftChild != nullptr && siblingNode->leftChild->type == TYPE_RED) {
            // case 1.2
            node->type = TYPE_BLACK;
            siblingNode->leftChild->type = TYPE_BLACK;
            siblingNode->type = parentNode->type;
            parentNode->type = TYPE_BLACK;
            rightRotate(parentNode);
        } else {
            // case 1.3
            // TODO: check
            node->type = TYPE_BLACK;
            siblingNode->rightChild->type = parentNode->type;
            parentNode->type = TYPE_BLACK;
            leftRotate(siblingNode);
            rightRotate(parentNode);
        }
    } else {
        // case 2
        parentNode->type = TYPE_RED;
        siblingNode->type = TYPE_BLACK;
        rightRotate(parentNode);
        handleDoubleBlack(node);
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
