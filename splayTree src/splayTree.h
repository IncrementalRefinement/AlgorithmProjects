//
// Created by 12638 on 2022/3/13.
//

#ifndef SRC_SPLAYTREE_H
#define SRC_SPLAYTREE_H
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

    void splay(NodePtr x);
    
};



#endif //SRC_SPLAYTREE_H
