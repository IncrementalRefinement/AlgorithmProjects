//
// Created by Xander on 2022/3/23.
//

#ifndef PROJ1_REDBLACKTREE_H
#define PROJ1_REDBLACKTREE_H

class RedBlackTree {
    class Node {
    public:
        Node(int);
        int key;
        Node *leftChild, *rightChild, *parent;
        int type;
        Node *getSibling();
    };

public:
    RedBlackTree();

    void Insert(int);

    bool Query(int);

    void Delete(int);

    void checkRep();

private:
    Node *root;

    Node *findNode(int);

    void Delete(int, Node*);

    void DeleteLeafNode(Node*);

    Node *leftRotate(Node *node);

    Node *rightRotate(Node *node);

    void handleDoubleRed(Node *node);

    void handleDoubleBlack(Node *node);

    Node *findMin(Node *node);
};

#endif //PROJ1_REDBLACKTREE_H
