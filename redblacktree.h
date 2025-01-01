#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <string>
#include <climits>

using namespace std;

enum Color {RED, BLACK};

class Node {
public:
    string word;
    int frequency;
    Color color;
    Node *left, *right, *parent;

    Node(string w, int f) : word(w), frequency(f), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class RedBlackTree {
public:
    Node* getRoot();
    Node* getTNULL();

    RedBlackTree();
    ~RedBlackTree();
    bool empty();
    void insert(string word);
    void countFrequency(ostream &out);
    void sortingfrequency(ostream &out);
    void graph(ostream &out) const;

public:
    Node* root;
    Node* TNULL;
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    Node* insertRec(Node* node, Node* newNode);
    void insertFix(Node* node);
    void inorderTraversal(ostream &out) const;
    void displayHelper(Node* node, ostream &out) const;
    void deleteSubtree(Node* node, Node* TNULL);
    void inorderHelperToCount(Node* node, int &maxFrequency, string &wordWithMaxFrequency) const;
    void graphAux(ostream &out, Node* node, int depth) const;
    void NodesToArray(Node* node, Node* nodes[], int &nodeCount);
};

#endif // REDBLACKTREE_H
