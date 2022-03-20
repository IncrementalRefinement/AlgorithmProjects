//
// Created by Xander on 2022/3/20.
//

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include "BST/BST.h"
#include "AvlTree/AvlTree.h"
// #include "SplayTree/splayTree.h"

using namespace std;

const int STEP_NUM = 20;
const int STEP_SIZE = 1000;
const int MIN_N = 1;
const int MAX_N = MIN_N + STEP_NUM * STEP_SIZE;
const double SKEWED_QUERY_PROPORTION = 0.1;
const string OUTPUT_FILE_LOCATION = "result.csv";


void TestIncreasingInsertOrder(ofstream &outputFile);
void TestRandomInsertOrder(ofstream &outputFile);
void TestRandomDeleteOrder(ofstream &outputFile);
void TestRandomQuery(ofstream &outputFile);
void TestSkewedQuery(ofstream &outputFile);

vector<string> TestIncreasingInsertOrder(int N);
vector<string> TestRandomInsertOrder(int N);
vector<string> TestRandomDeleteOrder(int N);
vector<string> TestRandomQuery(int N);
vector<string>TestSkewedQuery(int N);

void TestIncreasingInsertOrder(ofstream &outputFile) {
    static string TestCase = "TestIncreasingInsertOrder";
    for (int i = MIN_N; i <= MAX_N; i += STEP_SIZE) {
        vector<string> results = TestIncreasingInsertOrder(i);
        for (const string& item : results) {
            outputFile << TestCase << ";" << item << endl;
        }
    }
}

void TestRandomInsertOrder(ofstream &outputFile) {
    static string TestCase = "TestRandomInsertOrder";
    for (int i = MIN_N; i <= MAX_N; i += STEP_SIZE) {
        vector<string> results = TestRandomInsertOrder(i);
        for (const string& item : results) {
            outputFile << TestCase << ";" << item << endl;
        }
    }
}

void TestRandomDeleteOrder(ofstream &outputFile) {
    static string TestCase = "TestRandomDeleteOrder";
    for (int i = MIN_N; i <= MAX_N; i += STEP_SIZE) {
        vector<string> results = TestRandomDeleteOrder(i);
        for (const string& item : results) {
            outputFile << TestCase << ";" << item << endl;
        }
    }
}

void TestRandomQuery(ofstream &outputFile) {
    static string TestCase = "TestRandomQuery";
    for (int i = MIN_N; i <= MAX_N; i += STEP_SIZE) {
        vector<string> results = TestRandomQuery(i);
        for (const string& item : results) {
            outputFile << TestCase << ";" << item << endl;
        }
    }
}

void TestSkewedQuery(ofstream &outputFile) {
    static string TestCase = "TestSkewedQuery";
    for (int i = MIN_N; i <= MAX_N; i += STEP_SIZE) {
        vector<string> results = TestSkewedQuery(i);
        for (const string& item : results) {
            outputFile << TestCase << ";" << item << endl;
        }
    }
}

vector<string> TestIncreasingInsertOrder(int N) {
    vector<string> ret;
    AvlTree avlTree;
    BST bst;
    vector<int> insertItems;
    clock_t  begin_time, end_time, delta_time;

    insertItems.resize(N);
    for (int i = 0; i < N; i++) {
        insertItems[i] = i;
    }
    begin_time = clock();
    for (int item : insertItems) {
        bst.Insert(item);
    }
    end_time = clock();
    delta_time = end_time - begin_time;
    // string temp = to_string(delta_time);

    ret.push_back(to_string(N) + ";" + "BST" + ";" + to_string(float(delta_time)));

    begin_time = clock();
    for (int item : insertItems) {
        avlTree.Insert(item);
    }
    end_time = clock();
    delta_time = end_time - begin_time;
    ret.push_back(to_string(N) + ";" + "AvlTree" + ";" + to_string(float(delta_time)));
    return ret;
}

vector<string> TestRandomInsertOrder(int N) {
    vector<string> ret;
    return ret;
}

vector<string> TestRandomDeleteOrder(int N) {
    vector<string> ret;
    return ret;
}

vector<string> TestRandomQuery(int N) {
    vector<string> ret;
    return ret;
}

vector<string>TestSkewedQuery(int N) {
    vector<string> ret;
    return ret;
}


/*
 * TestCase; N; TreeType; TimeCost
 */
int main() {
    ofstream resultFile;
    resultFile.open(OUTPUT_FILE_LOCATION, fstream::in | fstream::out | fstream::app);
    TestIncreasingInsertOrder(resultFile);
    TestRandomInsertOrder(resultFile);
    TestRandomDeleteOrder(resultFile);
    TestRandomQuery(resultFile);
    TestSkewedQuery(resultFile);
    resultFile.close();
}