#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

class BST
{
private:
    struct Node
    {
        int value;
        Node *lchild;
        Node *rchild;
        Node() : value(-1), lchild(nullptr), rchild(nullptr) {}
    };

    struct Search_result
    {
        bool exists;
        Node *node;   // return node addr if result exists
        Node *parent; // return parent addr if result doesn't exist
        Search_result() : exists(false), node(nullptr), parent(nullptr) {}
    };

public:
    BST();
    ~BST();

private:
    Node *root;
    Node *current;
    Search_result find(const int &);
};

#endif