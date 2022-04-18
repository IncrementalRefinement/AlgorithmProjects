//
// Created by Xander on 2022/4/18.
//

#ifndef PROJ4_HUFFMANTREE_H
#define PROJ4_HUFFMANTREE_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const char INVALID_CHAR = -1;

class HuffmanTree {

private:
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

    ~HuffmanTree() {
        delete this->left;
        delete this->right;
    }

    HuffmanTree* merge(HuffmanTree* otherTree);
    unsigned long getTreeWeight();
    unordered_map<char, string> getHuffmanCode();
};

bool isCodeLegal(unordered_map<char, string> codeToCheck, vector<char> theChars, vector<unsigned long> theFrequencies);

#endif //PROJ4_HUFFMANTREE_H
