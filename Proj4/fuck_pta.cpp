//
// Created by Xander on 2022/4/18.
//

#ifndef PROJ4_HUFFMANTREE_H
#define PROJ4_HUFFMANTREE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

const char INVALID_CHAR = -1;

class HuffmanTree {

public:
    char theChar;
    unsigned long weight;
    HuffmanTree *left;
    HuffmanTree *right;

public:
    explicit HuffmanTree(unsigned long theWeight) {
        this->weight = theWeight;
        this->left = nullptr;
        this->right = nullptr;
        this->theChar = INVALID_CHAR;
    }

    HuffmanTree(unsigned long theWeight, char theChar) {
        this->weight = theWeight;
        this->left = nullptr;
        this->right = nullptr;
        this->theChar = theChar;
    }

    HuffmanTree* merge(HuffmanTree* otherTree);
    unsigned long getTreeWeight();
    unordered_map<char, string> getHuffmanCode();
};

bool isCodeLegal(unordered_map<char, string> codeToCheck, vector<char> theChars, vector<unsigned long> theFrequencies);

#endif //PROJ4_HUFFMANTREE_H


#include <cassert>
#include <algorithm>
#include <queue>



typedef struct BinaryTreeNode {
    BinaryTreeNode *left;
    BinaryTreeNode *right;

public:
    BinaryTreeNode() {
        this->left = nullptr;
        this->right = nullptr;
    }
} BinaryTreeNode;

class HuffmanTreeComparator {
public:
    bool operator() (HuffmanTree *a, HuffmanTree *b) {
        return a->getTreeWeight() > b->getTreeWeight();
    }
};

void dfs(HuffmanTree *currentNode, unordered_map<char, string>& huffmanCode, const string& theCode);
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
    unordered_map<char, string> huffmanCode = unordered_map<char, string>();
    dfs(this, huffmanCode, "");
    return huffmanCode;
}

bool isCodeLegal(unordered_map<char, string> codeToCheck, vector<char> theChars, vector<unsigned long> theFrequencies) {
    assert(theChars.size() == theFrequencies.size());

    // 1. check if the code is legal prefix code
    if (!isPrefixCode(codeToCheck)) {
        return false;
    }
    // 2. generate huffmanTree array with theChars & theFrequencies, sort the array
    priority_queue<HuffmanTree*, vector<HuffmanTree*>, HuffmanTreeComparator> pq;

    for (unsigned int i = 0; i < theChars.size(); i++) {
        HuffmanTree *newTree = new HuffmanTree(theFrequencies[i], theChars[i]);
        pq.push(newTree);
    }

    // 3. merge the trees to one HuffmanTree
    while (pq.size() > 1) {
        HuffmanTree* t1 = pq.top();
        pq.pop();
        HuffmanTree* t2 = pq.top();
        pq.pop();
        HuffmanTree* t3 = t1->merge(t2);
        pq.push(t3);
    }

    // 4. check if the code length is optimal
    HuffmanTree* theOptimalTree = (pq.top());
    pq.pop();
    unordered_map<char, string> optimalCode = theOptimalTree->getHuffmanCode();
    unsigned long optimalLength = 0;
    unsigned long actualLength = 0;
    for (unsigned int i = 0; i < theChars.size(); i++) {
        char theChar = theChars[i];
        unsigned long frequency = theFrequencies[i];
        optimalLength += optimalCode[theChar].length() * frequency;
        actualLength += codeToCheck[theChar].length() * frequency;
    }
    // delete &optimalCode;
    delete theOptimalTree;
    assert(optimalLength <= actualLength);
    return optimalLength == actualLength;
}

void dfs(HuffmanTree *currentNode, unordered_map<char, string>& huffmanCode, const string& theCode) {
    if (currentNode == nullptr) return;
    if (currentNode->left == nullptr && currentNode -> right == nullptr) {
        huffmanCode[currentNode->theChar] = theCode;
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

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<char> theChars;
    theChars.reserve(N);
    vector<unsigned long> theFrequencies;
    theFrequencies.reserve(N);

    for (int i = 0; i < N; i++) {
        char theChar;
        unsigned long theFrequency;
        cin >> theChar;
        cin >> theFrequency;
        theChars.push_back(theChar);
        theFrequencies.push_back(theFrequency);
    }

    int checkTimes;
    cin >> checkTimes;
    for (int i = 0; i < checkTimes; i++) {
        unordered_map<char, string> codeToCheck;
        for (int j = 0; j < N; j++) {
            char theChar;
            string theCode;
            cin >> theChar;
            cin >> theCode;
            codeToCheck[theChar] = theCode;
        }
        if (isCodeLegal(codeToCheck, theChars, theFrequencies)) {
            cout << "Yes";
        } else {
            cout << "No";
        }
        if (i < checkTimes - 1) {
            cout << endl;
        }
    }
}
