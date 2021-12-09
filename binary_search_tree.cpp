#include "binary_search_tree.h"
#include <iostream>

using namespace std;

BST::BST()
{
    root = new Node;
    current = root;
}

BST::~BST()
{
    // delete child nodes
    delete root;
}

BST::Search_result BST::find(const int &x)
{
    Search_result result;

    while (current)
    {
        result.parent = current;

        if (x < current->value)
            current = current->lchild;
        else if (x > current->value)
            current = current->rchild;
        else
        {
            result.exists = true;
            result.node = current;
            break;
        }
    }

    current = root;
    return result;
}