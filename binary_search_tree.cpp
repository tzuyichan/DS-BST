#include "binary_search_tree.h"
#include <iostream>

using namespace std;

BST::BST()
{
    root = new Node;
}

BST::~BST()
{
    // delete child nodes
    delete root;
}