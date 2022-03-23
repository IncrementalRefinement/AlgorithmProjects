//
// Created by 12638 on 2022/3/20.
//
#include <assert.h>
#include "RedBlackTree.h"

// Implementing Red-Black Tree in C++

RBTnodePtr RedBlackTree::searchTreeHelper(RBTnodePtr node, int key) {
    if (node == TNULL || key == node->data) {
        return node;
    }

    if (key < node->data) {
        return searchTreeHelper(node->left, key);
    } else
        return searchTreeHelper(node->right, key);
}

RBTnodePtr RedBlackTree::minimum(RBTnodePtr node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

// For balancing the tree after deletion
void RedBlackTree::deleteFix(RBTnodePtr x) {
    RBTnodePtr s;

    while (x != root && x->color == 0) {
        if (x == x->parent->left) {
            s = x->parent->right;
            //the sibling of x  is red,
            //Case-I:
            if (s->color == 1) {
                s->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                s = x->parent->right;
            }
            //If the sibling has two BLACK children.
            //Case-II:
            if (s->left->color == 0 && s->right->color == 0) {
                s->color = 1;
                x = x->parent;
            } else {
                //Case-III:
                if (s->right->color == 0) {
                    s->left->color = 0;
                    s->color = 1;
                    rightRotate(s);
                    s = x->parent->right;
                }
                // case IV
                s->color = x->parent->color;
                x->parent->color = 0;
                s->right->color = 0;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            //Else the same as above with right changed to left and vice versa.
            s = x->parent->left;
            if (s->color == 1) {
                s->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == 0) {
                s->color = 1;
                x = x->parent;
            } else {
                if (s->left->color == 0) {
                    s->right->color = 0;
                    s->color = 1;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = 0;
                s->left->color = 0;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 0;
}

void RedBlackTree::rbTransplant(RBTnodePtr u, RBTnodePtr v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RedBlackTree::insertFix(RBTnodePtr k) {
    RBTnodePtr u;
    //Do the following while the parent of newNode p is RED.
    while (k->parent->color == 1) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            //If the sibling is RED,
            // set the color of both the children of gP as BLACK and the color of gP as RED.
            if (u->color == 1) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;//Assign gP to newNode.
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                //Set color of p as BLACK and color of gP as RED.
                k->parent->color = 0;
                k->parent->parent->color = 1;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;

            if (u->color == 1) {
                //set the color of both the children of gP as BLACK and the color of gP as RED.
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;//Assign gP to newNode
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                //Set color of p as BLACK and color of gP as RED.
                k->parent->color = 0;
                k->parent->parent->color = 1;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = 0;//Set the root of the tree as BLACK.
}

RedBlackTree::RedBlackTree() {
    TNULL = new RBTnode();
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

RBTnodePtr RedBlackTree::Query(int k) {
    return searchTreeHelper(this->root, k);
}


void RedBlackTree::leftRotate(RBTnodePtr x) {
    RBTnodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(RBTnodePtr x) {
    RBTnodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RedBlackTree::Insert(int key) {
    RBTnodePtr node = new RBTnode();
    node->parent = nullptr;
    node->data = key;
    //Assign `Nil` to the left and right Child of newNode.
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;//Assign RED color to newNode.

    RBTnodePtr y = nullptr;// y is the parent of x
    RBTnodePtr x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    //find the leaf node as search in a binary search tree.
    if (y == nullptr) {
        root = node;//Check if the tree is empty (ie. whether x is `NIL`).
        // If yes, insert new RedBlackTreeNode as a root node and color it black.
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = 0;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    insertFix(node);
}


void RedBlackTree::Delete(int key) {
    RBTnodePtr node = root;
    RBTnodePtr z = TNULL;
    RBTnodePtr x, y;
    while (node != TNULL) {
        if (node->data == key) {
            z = node;
        }

        if (node->data <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        cout << "Key not found in the tree" << endl;
        return;
    }

    y = z;
    //Save the color of nodeToBeDeleted in origrinalColor.
    int y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y);
        //Set the color of y with originalColor.
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    //If the originalColor is BLACK, invoke DeleteFix(x).
    if (y_original_color == 0) {
        deleteFix(x);
    }
}


//int main() {
//    RedBlackTree rbt;
//    rbt.Insert(55);
//    rbt.Insert(40);
//    rbt.Insert(65);
//    rbt.Insert(60);
//    rbt.Insert(75);
//    rbt.Insert(57);
////    for (int i = 0; i < 1000; i++) {
////        rbt.Insert(i);
////    }
////    for (int i = 0; i < 1000; i++) {
////        rbt.Query(i);
////    }
////    for (int i = 0; i < 1000; i++) {
////        rbt.Delete(i);
////    }
////    for (int i = 0; i < 1000; i++) {
////        rbt.Query(i);
////    }
////    rbt.printTree();
////    cout << endl
////         << "After deleting" << endl;
//    rbt.Delete(40);
//};