#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include "HuffmanTree.h"

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

    int checkTime;
    cin >> checkTime;
    for (int i = 0; i < checkTime; i++) {
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
        if (i < checkTime - 1) {
            cout << endl;
        }
    }
}
