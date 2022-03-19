#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Node {
    int data;
    Node *parent;
    Node *left;
    Node *right;
};

typedef Node *NodePtr;

class SplayTree {
private:


    NodePtr searchTree(NodePtr node, int key) {
        if (node == nullptr || key == node->data) {
            return node;
        }
        if (key < node->data) {
            return searchTree(node->left, key);
        } else {
            return searchTree(node->right, key);
        }
    }


    void split(NodePtr& x, NodePtr &s, NodePtr& t) {
        splay(x);
        t = x->right;
        s = x;
        if (t != nullptr)
            t->parent = nullptr;
        s->right = nullptr;
        x = nullptr;
    }

    NodePtr join(NodePtr left, NodePtr right) {
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


    void leftRotate(NodePtr x) {
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

    void rightRotate(NodePtr x) {
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

    string serailize(NodePtr root) {
        if (root == nullptr) {
            return "#";
        }
        return to_string(root->data) + ' ' + serailize(root->left) + ' ' + serailize(root->right);
    }

    void splay(NodePtr x) {
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

public:
    NodePtr root;

    SplayTree() {
        root = nullptr;
    }

    NodePtr findKey(int k) {
        NodePtr x = searchTree(this->root, k);
        if (x != nullptr)
            splay(x);
        return x;
    }

    void insert(int key) {
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

    void deleteKey(int key) {
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
            cout << "Couldn't find key in the tree" << endl;
            return;
        }
        // split to s, t two subTree
        split(x, s, t);
        if (s->left != nullptr) {
            s->left->parent = nullptr;// remove x
        }
        this->root = join(s->left, t);
        delete (s);
        s = nullptr;
    }

    void print(NodePtr root) {
        cout << serailize(root) << endl;
        return;
    }
};


int main() {
    SplayTree bst;
    bst.insert(33);
    bst.insert(44);
    bst.insert(67);
    bst.insert(5);
    bst.insert(89);
    bst.insert(41);
    bst.insert(98);
    bst.insert(1);
    bst.print(bst.root);
    bst.findKey(33);
    bst.findKey(44);
    bst.print(bst.root);
    bst.deleteKey(89);
    bst.deleteKey(67);
    bst.deleteKey(41);
    bst.deleteKey(5);
    bst.print(bst.root);
    bst.deleteKey(98);
    bst.deleteKey(1);
    bst.deleteKey(44);
    bst.deleteKey(33);
    bst.print(bst.root);
    return 0;
}
