//
// Created by Xander on 2022/4/18.
//

#include "HuffmanTree.h"

typedef struct BinaryTreeNode {
    BinaryTreeNode *left;
    BinaryTreeNode *right;
} BinaryTreeNode;

HuffmanTree *HuffmanTree::merge(HuffmanTree *otherTree) {
    HuffmanTree *newTree = new HuffmanTree(this->getTreeWeight() + otherTree->getTreeWeight());
    newTree->left = this;
    newTree->right = otherTree;
    return newTree;
}

unsigned long HuffmanTree::getTreeWeight() {
    return this->weight;
}

unordered_map<char, string> HuffmanTree::getHuffmanCode() {
    return unordered_map<char, string>();
}

bool isCodeLegal(unordered_map<char, string> codeToCheck, vector<char> theChars, vector<unsigned long> theFrequencies) {
    return false;
}