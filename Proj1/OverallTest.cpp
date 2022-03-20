//
// Created by Xander on 2022/3/20.
//

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>


#include "BST/BST.h"
#include "AvlTree/AvlTree.h"
// #include "SplayTree/splayTree.h"

using namespace std;

const int STEP_NUM = 20;
const int STEP_SIZE = 1000;
const int MIN_N = 1;
const int MAX_N = MIN_N + STEP_NUM * STEP_SIZE;
const double SKEWED_QUERY_PROPORTION = 0.1;
const char *const OUTPUT_FILE_LOCATION = "result.csv";


void TestIncreasingInsertOrder(ofstream &outputFile);
void TestRandomInsertOrder(ofstream &outputFile);
void TestRandomDeleteOrder(ofstream &outputFile);
void TestRandomQuery(ofstream &outputFile);
void TestSkewedQuery(ofstream &outputFile);

vector<string> TestIncreasingInsertOrder(int N);
vector<string> TestRandomInsertOrder(int N);
vector<string> TestRandomDeleteOrder(int N);
vector<string> TestRandomQuery(int N);
vector<string> TestSkewedQuery(int N);

// TODO: the code is really verbose and repeated, need refactor

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
    chrono::time_point<chrono::system_clock, chrono::nanoseconds>  begin_time, end_time;
    long long delta_time;
    insertItems.resize(N);
    for (int i = 0; i < N; i++) {
        insertItems[i] = i;
    }

    begin_time = std::chrono::high_resolution_clock::now();
    for (int item : insertItems) {
        bst.Insert(item);
    }
    end_time = std::chrono::high_resolution_clock::now();
    delta_time = (end_time - begin_time).count();
    ret.push_back(to_string(N) + ";" + "BST" + ";" + to_string(delta_time));

    begin_time = std::chrono::high_resolution_clock::now();
    for (int item : insertItems) {
        avlTree.Insert(item);
    }
    end_time = std::chrono::high_resolution_clock::now();
    delta_time = (end_time - begin_time).count();
    ret.push_back(to_string(N) + ";" + "AvlTree" + ";" + to_string(delta_time));

    return ret;
}

vector<string> TestRandomInsertOrder(int N) {
    vector<string> ret;
    AvlTree avlTree;
    BST bst;
    vector<int> insertItems;
    chrono::time_point<chrono::system_clock, chrono::nanoseconds>  begin_time, end_time;
    long long delta_time;

    insertItems.resize(N);
    for (int i = 0; i < N; i++) {
        insertItems[i] = i;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(insertItems.begin(), insertItems.end(), default_random_engine(seed));

    begin_time = std::chrono::high_resolution_clock::now();
    for (int item : insertItems) {
        bst.Insert(item);
    }
    end_time = std::chrono::high_resolution_clock::now();
    delta_time = (end_time - begin_time).count();
    ret.push_back(to_string(N) + ";" + "BST" + ";" + to_string(delta_time));

    begin_time = std::chrono::high_resolution_clock::now();
    for (int item : insertItems) {
        avlTree.Insert(item);
    }
    end_time = std::chrono::high_resolution_clock::now();
    delta_time = (end_time - begin_time).count();
    ret.push_back(to_string(N) + ";" + "AvlTree" + ";" + to_string(delta_time));

    return ret;
}

vector<string> TestRandomDeleteOrder(int N) {
    vector<string> ret;
    AvlTree avlTree;
    BST bst;
    vector<int> items;
    chrono::time_point<chrono::system_clock, chrono::nanoseconds>  begin_time, end_time;
    long long delta_time;

    items.resize(N);
    for (int i = 0; i < N; i++) {
        items[i] = i;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(items.begin(), items.end(), default_random_engine(seed));

    // construct trees by random insert
    for (int item : items) {
        bst.Insert(item);
    }

    for (int item : items) {
        avlTree.Insert(item);
    }

    // test random delete
    seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(items.begin(), items.end(), default_random_engine(seed));

    begin_time = std::chrono::high_resolution_clock::now();
    for (int item : items) {
        bst.Delete(item);
    }
    end_time = std::chrono::high_resolution_clock::now();
    delta_time = (end_time - begin_time).count();
    ret.push_back(to_string(N) + ";" + "BST" + ";" + to_string(delta_time));

    begin_time = std::chrono::high_resolution_clock::now();
    for (int item : items) {
        avlTree.Delete(item);
    }
    end_time = std::chrono::high_resolution_clock::now();
    delta_time = (end_time - begin_time).count();
    ret.push_back(to_string(N) + ";" + "AvlTree" + ";" + to_string(delta_time));

    return ret;
}

vector<string> TestRandomQuery(int N) {
    vector<string> ret;
    AvlTree avlTree;
    BST bst;
    vector<int> items;
    chrono::time_point<chrono::system_clock, chrono::nanoseconds>  begin_time, end_time;
    long long delta_time;

    items.resize(N);
    for (int i = 0; i < N; i++) {
        items[i] = i;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(items.begin(), items.end(), default_random_engine(seed));

    // construct trees by random insert
    for (int item : items) {
        bst.Insert(item);
    }

    for (int item : items) {
        avlTree.Insert(item);
    }

    // test random query
    seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(items.begin(), items.end(), default_random_engine(seed));

    begin_time = std::chrono::high_resolution_clock::now();
    for (int item : items) {
        bst.Query(item);
    }
    end_time = std::chrono::high_resolution_clock::now();
    delta_time = (end_time - begin_time).count();
    ret.push_back(to_string(N) + ";" + "BST" + ";" + to_string(delta_time));

    begin_time = std::chrono::high_resolution_clock::now();
    for (int item : items) {
        avlTree.Query(item);
    }
    end_time = std::chrono::high_resolution_clock::now();
    delta_time = (end_time - begin_time).count();
    ret.push_back(to_string(N) + ";" + "AvlTree" + ";" + to_string(delta_time));

    return ret;
}

vector<string>TestSkewedQuery(int N) {
    vector<string> ret;
    AvlTree avlTree;
    BST bst;
    vector<int> insertItems, queryItems;
    chrono::time_point<chrono::system_clock, chrono::nanoseconds> begin_time, end_time;
    long long delta_time;

    insertItems.resize(N);
    for (int i = 0; i < N; i++) {
        insertItems[i] = i;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(insertItems.begin(), insertItems.end(), default_random_engine(seed));

    // construct trees by random insert
    for (int item : insertItems) {
        bst.Insert(item);
    }

    for (int item : insertItems) {
        avlTree.Insert(item);
    }

    // test random skewed query
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(insertItems.begin(), insertItems.end(), default_random_engine(seed));
    for (int i = 0; i < N * SKEWED_QUERY_PROPORTION; i++) {
        for (int j = 0; j < (1 / SKEWED_QUERY_PROPORTION); j++) {
            queryItems.push_back(insertItems[i]);
        }
    }
    shuffle(queryItems.begin(), queryItems.end(), default_random_engine(seed));

    begin_time = std::chrono::high_resolution_clock::now();
    for (int item : queryItems) {
        bst.Query(item);
    }
    end_time = std::chrono::high_resolution_clock::now();
    delta_time = (end_time - begin_time).count();
    ret.push_back(to_string(N) + ";" + "BST" + ";" + to_string(delta_time));

    begin_time = std::chrono::high_resolution_clock::now();
    for (int item : queryItems) {
        avlTree.Query(item);
    }
    end_time = std::chrono::high_resolution_clock::now();
    delta_time = (end_time - begin_time).count();
    ret.push_back(to_string(N) + ";" + "AvlTree" + ";" + to_string(delta_time));

    return ret;
}


/*
 * TestCase; N; TreeType; TimeCost
 */
int main() {
    ofstream resultFile;
    remove(OUTPUT_FILE_LOCATION);
    resultFile.open(OUTPUT_FILE_LOCATION, fstream::in | fstream::out | fstream::app);
    TestIncreasingInsertOrder(resultFile);
    TestRandomInsertOrder(resultFile);
    TestRandomDeleteOrder(resultFile);
    TestRandomQuery(resultFile);
    TestSkewedQuery(resultFile);
    resultFile.close();
}