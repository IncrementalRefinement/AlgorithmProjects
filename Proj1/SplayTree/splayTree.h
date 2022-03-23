//
// Created by 12638 on 2022/3/13.
//

#ifndef SRC_SPLAYTREE_H
#define SRC_SPLAYTREE_H

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
    NodePtr searchTree(NodePtr node, int key);


    void split(NodePtr &x, NodePtr &s, NodePtr &t);

    NodePtr join(NodePtr left, NodePtr right);


    void leftRotate(NodePtr x);

    void rightRotate(NodePtr x);

    string serailize(NodePtr root);

    void splay(NodePtr x);

    NodePtr Delete(NodePtr node, int key);

    int FindMinValue(NodePtr node);

    NodePtr root;
    bool is_splay_limit;
    int current_splay_number;
    int max_splay_number;

public:

    SplayTree();

    SplayTree(int N);

    NodePtr Query(int k);

    void Insert(int key);

    void Delete(int key);

    void print(NodePtr root);
};


#endif //SRC_SPLAYTREE_H
