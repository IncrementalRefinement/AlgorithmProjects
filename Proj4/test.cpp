//
// Created by Xander on 2022/4/19.
//

#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

#include "HuffmanTree.h"

const unsigned int MAX_CHAR_NUM = 63;
const unsigned int DEFAULT_TEST_TIMES = 10000;
const char *const TEST_DATA_FILE_LOCATION = "data.csv";
const char *const TEST_RESULT_FILE_LOCATION = "result.csv";

string convertToStringCode(unsigned char theCode);
void writeTestData(ofstream&, unsigned int, const unordered_map<char, string>&, vector<char>, vector<unsigned long>);

int main() {
    // 1. build the test case
    vector<char> theChars;
    vector<unsigned long> theFrequencies;
    vector<string> theCodes;
    unsigned char theCode= -1;
    unsigned long theFrequency = 0;

    for (char i = '0'; i <= '9'; i++) {
        theChars.push_back(i);
        theFrequencies.push_back(theFrequency);
        theCodes.push_back(convertToStringCode(theCode));
        theCode--;
        theFrequency++;
    }

    for (char i = 'a'; i <= 'z'; i++) {
        theChars.push_back(i);
        theFrequencies.push_back(theFrequency);
        theCodes.push_back(convertToStringCode(theCode));
        theCode--;
        theFrequency++;
    }

    for (char i = 'A'; i <= 'Z'; i++) {
        theChars.push_back(i);
        theFrequencies.push_back(theFrequency);
        theCodes.push_back(convertToStringCode(theCode));
        theCode--;
        theFrequency++;
    }

    theChars.push_back('_');
    theFrequencies.push_back(theFrequency);
    theCodes.push_back(convertToStringCode(theCode));

    // 2. do test
    ofstream resultFile, dataFile;
    remove(TEST_RESULT_FILE_LOCATION);
    remove(TEST_DATA_FILE_LOCATION);
    resultFile.open(TEST_RESULT_FILE_LOCATION, fstream::in | fstream::out | fstream::app);
    dataFile.open(TEST_DATA_FILE_LOCATION, fstream::in | fstream::out | fstream::app);

    for (unsigned int i = 1; i < MAX_CHAR_NUM; i++) {
        chrono::time_point<chrono::system_clock, chrono::nanoseconds>  begin_time, end_time;

        // generate the test data
        unordered_map<char, string> codeToCheck;
        vector<char> currentChars = {theChars.begin(), theChars.begin() + i + 1};
        vector<unsigned long> currentFrequencies = {theFrequencies.begin(), theFrequencies.begin() + i + 1};
        for (int j = 0; j <= i; j++) {
            codeToCheck[currentChars[j]] = theCodes[j];
        }
        writeTestData(dataFile, i, codeToCheck, currentChars, currentFrequencies);
        // do test
        begin_time = std::chrono::high_resolution_clock::now();
        for (int time = 0; time < DEFAULT_TEST_TIMES; time++) {
            assert(!isCodeLegal(codeToCheck, currentChars, currentFrequencies));
        }
        end_time = std::chrono::high_resolution_clock::now();
        long long deltaTime = (end_time- begin_time).count();

        // write test result and test data to the output file
        resultFile << i << ";" << deltaTime << endl;
    }

    resultFile.close();
    dataFile.close();
}

string convertToStringCode(unsigned char theCode) {
    string ret = "";

    while (theCode != 0) {
        if ((theCode & 1) == 1) {
            ret = "1" + ret;
        } else {
            ret = "0" + ret;
        }
        theCode = theCode >> 1;
    }

    while (ret.size() < 8) {
        ret = "0" + ret;
    }

    return ret;
}

void writeTestData(ofstream& output, unsigned int currentScale, const unordered_map<char, string>& codeToCheck, vector<char> theChars, vector<unsigned long> theFrequencies) {
    output << "=============================" << endl;
    output << "input scale: " << currentScale << endl;
    for (int i = 0; i < theChars.size(); i++) {
        output << theChars[i] << ": " << theFrequencies[i] << endl;
    }
    for (const auto& kv: codeToCheck) {
        output << kv.first << ": " << kv.second << endl;
    }
    output << "=============================" << endl;
}