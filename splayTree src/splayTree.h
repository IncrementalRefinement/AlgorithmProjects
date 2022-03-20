//
// Created by 12638 on 2022/3/13.
//

#ifndef SRC_SPLAYTREE_H
#define SRC_SPLAYTREE_H

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

    NodePtr searchTree(NodePtr node, int key);

    void deleteNode(NodePtr node, int key);

    void split(NodePtr x, NodePtr s, NodePtr t);

    NodePtr join(NodePtr left, NodePtr right);

    void print(NodePtr root, string indent, bool last);

    void leftRotate(NodePtr x);

    void rightRotate(NodePtr x);

    string serailize(NodePtr root);

    void splay(NodePtr x);

public:
    NodePtr root;

    SplayTree();

    NodePtr Query(int k);

    void Insert(int key);

    void Delete(int key);

    void print(NodePtr root);
};




#endif //SRC_SPLAYTREE_H
