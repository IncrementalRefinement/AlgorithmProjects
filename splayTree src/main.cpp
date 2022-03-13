#include <iostream>

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
    NodePtr root;

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

    void deleteNode(NodePtr node, int key) {
        NodePtr x = nullptr;
        NodePtr t, s;
        //find node
        while (node != nullptr) {
            if (node->data == key) {
                x = node;
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

    void split(NodePtr x, NodePtr s, NodePtr t) {
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
        return p ;
    }

    void print(NodePtr root, string indent, bool last) {
        if (root != nullptr) {
            cout << indent;
            if (last) {
                cout << "└────";
                indent += "";
            } else {
                cout << "├────";
                indent += "|    ";
            }
            cout << root->data << endl;
            print(root->left, indent, false);
            print(root->right, indent, true);
        }
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


};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
