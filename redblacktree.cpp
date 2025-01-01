#include "RedBlackTree.h"
#include <iostream>
#include <iomanip>
#include <climits>

using namespace std;

RedBlackTree::RedBlackTree() {
    TNULL = new Node("", 1);
    TNULL->color = BLACK;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    TNULL->parent = nullptr;
    root = TNULL;
}
bool RedBlackTree::empty() {
    return root == TNULL;
}
Node* RedBlackTree::getRoot() {
    return root;
}
// Getter for TNULL sentinel
Node* RedBlackTree::getTNULL() {
    return TNULL;
}
RedBlackTree::~RedBlackTree()
{

}


void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != TNULL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
void RedBlackTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RedBlackTree::insert(string word) {
    Node* newNode = new Node(word, 1);
    newNode->left = TNULL;
    newNode->right = TNULL;
    root = insertRec(root, newNode);
    insertFix(newNode);
}
Node* RedBlackTree::insertRec(Node* node, Node* newNode) {
    if (node == TNULL) {
        return newNode;
    }

    if (newNode->word < node->word) {
        node->left = insertRec(node->left, newNode);
        node->left->parent = node;
    } else if (newNode->word > node->word) {
        node->right = insertRec(node->right, newNode);
        node->right->parent = node;
    } else { // Word already exists, increment frequency
        node->frequency += newNode->frequency;
        delete newNode;
        return node;
    }
    return node;
}
void RedBlackTree::insertFix(Node* node) {
    Node* uncle;
    while (node->parent && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            uncle = node->parent->parent->right;
            if (uncle && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(node->parent->parent);
            }
        } else {
            uncle = node->parent->parent->left;
            if (uncle && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}


void RedBlackTree::countFrequency(ostream &out) {
    if (root == TNULL) {
        out << "Tree is empty.\nMax Frequency: 0\n";
        return;
    }

    string wordWithMaxFrequency;
    int maxFrequency = INT_MIN;
    inorderHelperToCount(root, maxFrequency, wordWithMaxFrequency);
    out << "Max Frequency: " << maxFrequency << " Word: " << wordWithMaxFrequency << endl;
}
void RedBlackTree::inorderHelperToCount(Node* node, int &maxFrequency, string &wordWithMaxFrequency) const {
    if (node != TNULL) {
        inorderHelperToCount(node->left, maxFrequency, wordWithMaxFrequency);
        if (node->frequency > maxFrequency) {
            maxFrequency = node->frequency;
            wordWithMaxFrequency = node->word;
        }
        inorderHelperToCount(node->right, maxFrequency, wordWithMaxFrequency);
    }
}



void RedBlackTree::sortingfrequency(ostream &out) {
    if (root == TNULL) {
        out << "Tree is empty.\n";
        return;
    }
    Node* nodes[100];
    int nodeCount = 0;
    NodesToArray(root, nodes, nodeCount);
    for (int i = 0; i < nodeCount - 1; ++i) {
        for (int j = 0; j < nodeCount - i - 1; ++j) {
            if (nodes[j]->frequency < nodes[j + 1]->frequency) {
                Node* temp = nodes[j];
                nodes[j] = nodes[j + 1];
                nodes[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < nodeCount; ++i) {
        out << "Word: " << nodes[i]->word << ", Frequency: " << nodes[i]->frequency << endl;
    }
}
void RedBlackTree::NodesToArray(Node* node, Node* nodes[], int &nodeCount) {
    if (node == TNULL) return;
    nodes[nodeCount++] = node;
    NodesToArray(node->left, nodes, nodeCount);
    NodesToArray(node->right, nodes, nodeCount);
}




void RedBlackTree::graph(ostream &out) const {
    graphAux(out, root, 5);
}
void RedBlackTree::graphAux(ostream &out, Node* node, int depth) const {
    if (node == TNULL) return;
    out << setw(depth * 8) << ' ';
    out << node->word << " (" << node->frequency << ")"
        << (node->color == RED ? " [RED]" : " [BLACK]") << endl;
    graphAux(out, node->left, depth + -2);
    graphAux(out, node->right, depth + 3);
}
