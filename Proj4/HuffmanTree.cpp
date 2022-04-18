//
// Created by Xander on 2022/4/18.
//

#include <cassert>
#include <algorithm>
#include <queue>

#include "HuffmanTree.h"

typedef struct BinaryTreeNode {
    BinaryTreeNode *left;
    BinaryTreeNode *right;

public:
    BinaryTreeNode() {
        this->left = nullptr;
        this->right = nullptr;
    }
} BinaryTreeNode;

void dfs(HuffmanTree *currentNode, unordered_map<char, string> *huffmanCode, const string& theCode);
bool isPrefixCode(const unordered_map<char, string>& codeToCheck);
bool conflictWithPrefixTree(const string& theCode, BinaryTreeNode *root);
void insertIntoTree(const string& theCode, BinaryTreeNode *root);

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
    unsigned long optimalLength = 0;
    unsigned long actualLength = 0;
    for (int i = 0; i < theChars.size(); i++) {
        char theChar = theChars[i];
        unsigned long frequency = theFrequencies[i];
        optimalLength += optimalCode[theChar].length() * frequency;
        actualLength += codeToCheck[theChar].length() * frequency;
    }
    delete &optimalCode;
    delete theOptimalTree;
    assert(actualLength <= optimalLength);
    return optimalLength == actualLength;
}

void dfs(HuffmanTree *currentNode, unordered_map<char, string> *huffmanCode, const string& theCode) {
    if (currentNode == nullptr) return;
    if (currentNode->left == nullptr && currentNode -> right == nullptr) {
        (*huffmanCode)[currentNode->theChar] = theCode;
        return;
    }
    dfs(currentNode->left, huffmanCode, theCode + "0");
    dfs(currentNode->right, huffmanCode, theCode + "1");
}

bool isPrefixCode(const unordered_map<char, string>& codeToCheck) {
    BinaryTreeNode *root = new BinaryTreeNode();
    // 1. construct the binary tree
    for (const auto& kv : codeToCheck) {
        insertIntoTree(kv.second, root);
    }
    // 2. check if conflict
    for (const auto& kv : codeToCheck) {
        if (conflictWithPrefixTree(kv.second, root)) {
            delete root;
            return false;
        }
    }
    delete root;
    return true;
}

bool conflictWithPrefixTree(const string& theCode, BinaryTreeNode *root) {
    BinaryTreeNode *ptr = root;
    int index = 0;
    while(index < theCode.size()) {
        if (theCode[index] == '0') {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
        index++;
    }
    if (ptr->left == nullptr && ptr->right == nullptr) return false;
    return true;
}

void insertIntoTree(const string& theCode, BinaryTreeNode *root) {
    BinaryTreeNode *ptr = root;
    int index = 0;
    while(index < theCode.size()) {
        if (theCode[index] == '0') {
            if (ptr->left == nullptr) {
                ptr->left = new BinaryTreeNode();
            }
            ptr = ptr->left;
        } else {
            if (ptr->right == nullptr) {
                ptr->right = new BinaryTreeNode();
            }
            ptr = ptr->right;
        }
        index++;
    }
}