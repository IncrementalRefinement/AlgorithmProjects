#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *parent;
    Node *left;
    Node *right;
};

typedef Node * NodePtr;

class SplayTree{
private:
    NodePtr root;


};




int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
