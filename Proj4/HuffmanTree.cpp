//
// Created by Xander on 2022/4/18.
//

#include "HuffmanTree.h"

void dfs(HuffmanTree *currentNode, unordered_map<char, string> huffmanCode, string theCode);

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
    unordered_map<char, string> huffmanCode = unordered_map<char, string>();
    dfs(this, huffmanCode, "");
    return huffmanCode;
}

bool isCodeLegal(unordered_map<char, string> codeToCheck, vector<char> theChars, vector<unsigned long> theFrequencies) {
    return false;
    // 1. check if the code is legal prefix code
    // 2. generate huffmanTree array with theChars & theFrequencies
    // 3. sort the array
    // 4. merge the tree and generate one HuffmanTree
    // 5. check if the code length is optimal
}

void dfs(HuffmanTree *currentNode, unordered_map<char, string> huffmanCode, string theCode) {
    if (currentNode == nullptr) return;
    if (currentNode->left == nullptr && currentNode -> right == nullptr) {
        huffmanCode[currentNode->theChar] = theCode;
        return;
    }
    dfs(currentNode->left, huffmanCode, theCode + "0");
    dfs(currentNode->right, huffmanCode, theCode + "1");
}