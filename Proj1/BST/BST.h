//
// Created by Xander on 2022/3/12.
//

#ifndef PROJ1_BST_H
#define PROJ1_BST_H

class BST {
    class BSTNode {
    public:
        BSTNode(int);
        int key;
        BSTNode *left;
        BSTNode *right;
    };
private:
    BSTNode *root;
public:
    BST();

    void Delete(int);

    void Insert(int);

    bool Query(int);

private:
    bool Query(BSTNode *node, int key);

    BSTNode *Delete(BSTNode *node, int key);

    BSTNode *Insert(BSTNode *node, int key);

    int FindMinValue(BSTNode *node);
};


#endif //PROJ1_BST_H
