#include "binary_search_tree.h"
#include <iostream>

using namespace std;

BST::BST() : root(nullptr)
{
}

BST::~BST()
{
    // delete child nodes
    // delete root;
}

void BST::insert(const int &x)
{
    Search_result result = find(x);
    if (result.exists)
    {
        cout << "Error. " << result.node->value << " already exists." << endl;
        return;
    }

    Node *new_node = new Node;
    new_node->value = x;

    if (!result.parent)
        root = new_node;
    else if (x < result.parent->value)
        result.parent->lchild = new_node;
    else
        result.parent->rchild = new_node;

    cout << new_node->value << " is inserted!" << endl;
}

void BST::insert(const vector<int> &input)
{
    for (const int &x : input)
        insert(x);
}

BST::Search_result BST::find(const int &x)
{
    Node *current = root;
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

    return result;
}

void BST::inorder()
{
    return inorder(root);
}

void BST::inorder(Node *start)
{
    if (start)
    {
        inorder(start->lchild);
        cout << start->value << " ";
        inorder(start->rchild);
    }
    cout << endl;
}