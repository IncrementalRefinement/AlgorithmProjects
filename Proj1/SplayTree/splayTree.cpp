#include <iostream>
#include <string>
#include <queue>

#include "splayTree.h"

using namespace std;



typedef Node *NodePtr;



NodePtr SplayTree::searchTree(NodePtr node, int key) {
    if (node == nullptr || key == node->data) {
        return node;
    }
    if (key < node->data) {
        return searchTree(node->left, key);
    } else {
        return searchTree(node->right, key);
    }
}


void SplayTree::split(NodePtr& x, NodePtr &s, NodePtr& t) {
    splay(x);
    t = x->right;
    s = x;
    if (t != nullptr)
        t->parent = nullptr;
    s->right = nullptr;
    x = nullptr;
}

NodePtr SplayTree::join(NodePtr left, NodePtr right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr)
        return left;
    NodePtr p = left;
    // find the node with the maximum key
    while (p->right) {
        p = p->right;
    }
    splay(p);
    right->parent = p;
    p->right = right;
    return p;
}


void SplayTree::leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
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

void SplayTree::rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

string SplayTree::serailize(NodePtr root) {
    if (root == nullptr) {
        return "#";
    }
    return to_string(root->data) + ' ' + serailize(root->left) + ' ' + serailize(root->right);
}

void SplayTree::splay(NodePtr x) {
    // check if exceed spay_limit
    if (is_splay_limit) {
        if (this->current_splay_number >= this->max_splay_number) {
            return;
        } else {
            this->current_splay_number += 1;
        }
    }

    while (x->parent != nullptr) {
        if (x->parent->parent == nullptr) {
            // x paretn is root
            if (x == x->parent->left) {
                rightRotate(x->parent);
                //zig rotation
            } else {
                //zag rotation
                leftRotate(x->parent);
            }
        } else if (x == x->parent->left && x->parent == x->parent->parent->left) {
            rightRotate(x->parent->parent);
            rightRotate(x->parent);
        } else if (x == x->parent->left && x->parent == x->parent->parent->right) {
            rightRotate(x->parent);
            leftRotate(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->right) {
            leftRotate(x->parent->parent);
            leftRotate(x->parent);
        } else {
            leftRotate(x->parent);
            rightRotate(x->parent);
        }
    }
}

SplayTree::SplayTree() {
    root = nullptr;
    this->is_splay_limit = false;
    this->current_splay_number = 0;
    this->max_splay_number = 0;
}

SplayTree::SplayTree(int N) {
    root = nullptr;
    this->is_splay_limit = true;
    this->current_splay_number = 0;
    this->max_splay_number = N;
}

NodePtr SplayTree::Query(int k) {
    NodePtr x = searchTree(this->root, k);

    if (x != nullptr)
        splay(x);
    return x;
}

void SplayTree::Insert(int key) {
    NodePtr node = new Node();
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->data = key;
    NodePtr ancestor = nullptr;
    NodePtr p = root;
    while (p != nullptr) {
        ancestor = p;
        if (p->data > node->data) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    node->parent = ancestor;
    if (ancestor == nullptr) {
        root = node;
    } else if (ancestor->data > node->data) {
        ancestor->left = node;
    } else {
        ancestor->right = node;
    }
    splay(node);
}

void SplayTree::Delete(int key) {
    if (is_splay_limit && (this->current_splay_number >= this->max_splay_number)) {
        root = Delete(root, key);
        return;
    }

    NodePtr x = nullptr;
    NodePtr t = nullptr;
    NodePtr s = nullptr;
    NodePtr node = root;
    //find node
    while (node != nullptr) {
        if (node->data == key) {
            x = node;
            break;
        }
        if (node->data <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    if (x == nullptr) {
        return;
    }
    // split to s, t two subTree
    {
        split(x, s, t);
        if (s->left != nullptr) {
            s->left->parent = nullptr;// remove x
        }
        this->root = join(s->left, t);
        delete (s);
        s = nullptr;
        this->current_splay_number += 2;
    }
}

void SplayTree::print(NodePtr root) {
    cout << serailize(root) << endl;
    return;
}


NodePtr SplayTree::Delete(NodePtr node, int key) {
    if (node == nullptr) return nullptr;
    if (node->data == key) {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left != nullptr && node->right != nullptr) {
            int newKey = FindMinValue(node->right);
            node->data = newKey;
            node->right = Delete(node->right, newKey);
            return node;
        } else if (node->left != nullptr) {
            NodePtr ret = node->left;
            delete node;
            return ret;
        } else {
            NodePtr ret = node->right;
            delete node;
            return ret;
        }
    } else if (node->data < key) {
        node->right = Delete(node->right, key);
    } else {
        node->left = Delete(node->left, key);
    }
    return node;
}

int SplayTree::FindMinValue(NodePtr node) {
    NodePtr ptr = node;
    while (ptr->left != nullptr) {
        ptr = ptr->left;
    }
    return ptr->data;
}

//int main() {
//    SplayTree bst;
//    bst.Insert(33);
//    bst.Insert(44);
//    bst.Insert(67);
//    bst.Insert(5);
//    bst.Insert(89);
//    bst.Insert(41);
//    bst.Insert(98);
//    bst.Insert(1);
//    bst.print(bst.root);
//    bst.Query(33);
//    bst.Query(44);
//    bst.print(bst.root);
//    bst.Delete(89);
//    bst.Delete(67);
//    bst.Delete(41);
//    bst.Delete(5);
//    bst.print(bst.root);
//    bst.Delete(98);
//    bst.Delete(1);
//    bst.Delete(44);
//    bst.Delete(33);
//    bst.print(bst.root);
//    return 0;
//}
