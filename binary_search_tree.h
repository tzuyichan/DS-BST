#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

class BST
{
public:
    BST();
    ~BST();

private:
    struct Node
    {
        int data;
        Node *lchild;
        Node *rchild;
        Node() : data(-1), lchild(nullptr), rchild(nullptr) {}
    };
    Node *root;
};

#endif