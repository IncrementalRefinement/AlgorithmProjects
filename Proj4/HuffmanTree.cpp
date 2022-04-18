//
// Created by Xander on 2022/4/18.
//

#include <cassert>
#include <algorithm>
#include <queue>

#include "HuffmanTree.h"

void dfs(HuffmanTree *currentNode, unordered_map<char, string> *huffmanCode, string theCode);
bool isPrefixCode(unordered_map<char, string> codeToCheck);

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
    unordered_map<char, string> *huffmanCode = new unordered_map<char, string>();
    dfs(this, huffmanCode, "");
    return *huffmanCode;
}

bool isCodeLegal(unordered_map<char, string> codeToCheck, vector<char> theChars, vector<unsigned long> theFrequencies) {
    assert(theChars.size() == theFrequencies.size());

    // 1. check if the code is legal prefix code
    if (!isPrefixCode(codeToCheck)) {
        return false;
    }
    // 2. generate huffmanTree array with theChars & theFrequencies, sort the array
    vector<HuffmanTree> huffmanTrees;
    huffmanTrees.reserve(theChars.size());
    for (int i = 0; i < theChars.size(); i++) {
        HuffmanTree newTree = HuffmanTree(theFrequencies[i], theChars[i]);
        huffmanTrees.push_back(newTree);
    }
    sort(huffmanTrees.begin(),
         huffmanTrees.end(),
         [](const HuffmanTree & a, const HuffmanTree & b) -> bool
    {
        return a.weight < b.weight;
    });
    // 3. merge the trees to one HuffmanTree
    queue<HuffmanTree*> queue1;
    queue<HuffmanTree*> queue2;
    for (auto & huffmanTree : huffmanTrees) {
        queue1.push(&huffmanTree);
    }
    while (queue1.size() + queue2.size() > 1) {
        HuffmanTree *tree1 = nullptr;
        HuffmanTree *tree2 = nullptr;
        if (queue1.empty()) {
            tree1 = queue2.front();
            queue2.pop();
            tree2 = queue2.front();
            queue2.pop();
        } else if (queue2.empty()) {
            tree1 = queue1.front();
            queue1.pop();
            tree2 = queue1.front();
            queue1.pop();
        } else {
            if (queue1.front()->getTreeWeight() < queue2.front()->getTreeWeight()) {
                tree1 = queue1.front();
                queue1.pop();
            } else {
                tree1 = queue2.front();
                queue2.pop();
            }
            if (queue1.empty()) {
                tree2 = queue2.front();
                queue2.pop();
            } else if (queue2.empty()) {
                tree2 = queue1.front();
                queue1.pop();
            } else {
                if (queue1.front()->getTreeWeight() < queue2.front()->getTreeWeight()) {
                    tree2 = queue1.front();
                    queue1.pop();
                } else {
                    tree2 = queue2.front();
                    queue2.pop();
                }
            }
        }
        assert(tree1 != nullptr && tree2 != nullptr);
        queue2.push(tree1->merge(tree2));
    }
    HuffmanTree *theOptimalTree = queue2.front();
    queue2.pop();
    assert(queue2.empty());
    // 4. check if the code length is optimal
    unordered_map<char, string> optimalCode = theOptimalTree->getHuffmanCode();
    for (auto kv : optimalCode) {
        if (codeToCheck[kv.first].size() != kv.second.size()) {
            delete &optimalCode;
            delete theOptimalTree;
            return false;
        }
    }
    delete &optimalCode;
    delete theOptimalTree;
    return true;
}

void dfs(HuffmanTree *currentNode, unordered_map<char, string> *huffmanCode, string theCode) {
    if (currentNode == nullptr) return;
    if (currentNode->left == nullptr && currentNode -> right == nullptr) {
        (*huffmanCode)[currentNode->theChar] = theCode;
        return;
    }
    dfs(currentNode->left, huffmanCode, theCode + "0");
    dfs(currentNode->right, huffmanCode, theCode + "1");
}

bool isPrefixCode(unordered_map<char, string> codeToCheck) {
    // TODO
    return true;
}