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
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
