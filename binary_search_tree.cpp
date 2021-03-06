#include "binary_search_tree.h"
#include <iostream>
#include <string>

using namespace std;

namespace Text
{
    const string red = "\033[0;31m";
    const string reset = "\033[0m";
}

extern const int INPUT_MAX_LEN;

BST::BST() : root(nullptr)
{
}

BST::~BST()
{
    destruct_tree(root);
}

/*
 * recursively destruct nodes in post order
 */
void BST::destruct_tree(Node *start)
{
    if (start)
    {
        destruct_tree(start->lchild);
        destruct_tree(start->rchild);
        delete start;
    }
}

int BST::root_value() const
{
    return root ? root->value : -1;
}

/* 
 * insert one node of value x
 */
void BST::insert(const int &x)
{
    // if value already exists, do nothing
    Search_result result = find(x);
    if (result.exists)
    {
        cout << Text::red
             << "Error. " << result.node->value << " already exists."
             << Text::reset << endl;
        return;
    }

    // insert new value
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

/*
 * find if a node of value x exists in the bst
 */
BST::Search_result BST::find(const int &x) const
{
    Node *current = root;
    Search_result result;

    // traverse tree
    while (current)
    {
        if (x == current->value) // value exists
        {
            result.exists = true;
            result.node = current;
            break;
        }
        else // go to next node
        {
            result.parent = current;
            current = x < current->value ? current->lchild : current->rchild;
        }
    }

    return result;
}

void BST::find(const vector<int> &input)
{
    for (const int &x : input)
    {
        Search_result result = find(x);
        if (result.exists)
            cout << "Bingo! " << result.node->value << " is found." << endl;
        else
            cout << Text::red << "Sorry. " << x << " is not found." << Text::reset << endl;
    }
}

/*
 * similar to BST::find(), but returns the path instead
 * returns a path from top -> bottom and another path from bottom -> top
 */
BST::Path BST::find_path(const int &src, const int &dst) const
{
    Search_result result = find(src);
    Node *current = result.node;
    Path path;

    while (current)
    {
        path.top_down.push(current->value);
        path.bottom_up.push(current->value);

        if (dst == current->value)
            return path;
        else
            current = dst < current->value ? current->lchild : current->rchild;
    }

    path.top_down = {};
    path.bottom_up = {};
    return path;
}

/*
 * find the least greatest child of node A
 */
BST::Search_result BST::find_next_larger_than(Node *target)
{
    Search_result result;

    if (!target->rchild)
        return result;

    // go to right subtree
    result.exists = true;
    result.parent = target;
    result.node = target->rchild;

    // traverse right subtree to find the smallest node
    while (result.node->lchild)
    {
        result.parent = result.node;
        result.node = result.node->lchild;
    }

    return result;
}

/*
 * return a list of node values that contain a specific digit 
 * e.g. 43 contains 4 and 3
 */
vector<int> BST::values_containing_digit(const int &x)
{
    vector<int> to_be_deleted(INPUT_MAX_LEN);
    int delete_cnt = 0; // how many nodes contain this digit

    queue<int> postorder_bst = get_postorder();

    while (!postorder_bst.empty())
    {
        string value = to_string(postorder_bst.front());
        postorder_bst.pop();

        // if node value contains this digit, add to list
        if (value.find(to_string(x)) != -1)
        {
            to_be_deleted.at(delete_cnt++) = stoi(value);
        }
    }
    to_be_deleted.resize(delete_cnt);

    return to_be_deleted;
}

/* 
 * remove a node of value x
 */
void BST::remove(const int &x)
{
    Search_result result = find(x);

    if (!result.exists)
    {
        cout << Text::red << x << " does not exist." << Text::reset << endl;
        return;
    }

    // if the node has a right subtree, replace the node with the
    // least greatest value in its right subtree
    if (result.node->rchild)
    {
        Search_result next_larger = find_next_larger_than(result.node);

        if (result.node == next_larger.parent) // new node is its right child
            result.node->rchild = next_larger.node->rchild;
        else
            next_larger.parent->lchild = next_larger.node->rchild;

        result.node->value = next_larger.node->value;
        delete next_larger.node;
    }
    // the node has a left subtree but not a right subtree
    else if (result.node->lchild)
    {
        Node *temp = result.node->lchild;

        result.node->value = temp->value;
        result.node->lchild = temp->lchild;
        result.node->rchild = temp->rchild;

        delete temp;
    }
    // the node is a leaf node
    else
    {
        if (result.node == root)
            root = nullptr;
        else if (result.node->value < result.parent->value)
            result.parent->lchild = nullptr;
        else
            result.parent->rchild = nullptr;

        delete result.node;
    }

    cout << x << " deleted!" << endl;
}

void BST::remove(const vector<int> &input)
{
    for (const int &x : input)
        remove(x);
}

void BST::inorder()
{
    cout << "Inorder: ";
    inorder(root);
    cout << endl;
}

void BST::inorder(Node *start)
{
    if (start)
    {
        inorder(start->lchild);
        cout << start->value << " ";
        inorder(start->rchild);
    }
}

void BST::preorder()
{
    cout << "Preorder: ";
    preorder(root);
    cout << endl;
}

void BST::preorder(Node *start)
{
    if (start)
    {
        cout << start->value << " ";
        preorder(start->lchild);
        preorder(start->rchild);
    }
}

void BST::postorder()
{
    cout << "Postorder: ";
    postorder(root);
    cout << endl;
}

void BST::postorder(Node *start)
{
    if (start)
    {
        postorder(start->lchild);
        postorder(start->rchild);
        cout << start->value << " ";
    }
}

queue<int> BST::get_postorder() const
{
    queue<int> bst;
    postorder(root, bst);
    return bst;
}

void BST::postorder(Node *start, queue<int> &bst) const
{
    if (start)
    {
        postorder(start->lchild, bst);
        postorder(start->rchild, bst);
        bst.push(start->value);
    }
}

void BST::level_order()
{
    queue<Node *> q;
    Node *current = root;

    cout << "Level order: ";

    while (current)
    {
        cout << current->value << " ";

        if (current->lchild)
            q.push(current->lchild);
        if (current->rchild)
            q.push(current->rchild);

        if (q.size() == 0)
            break;

        current = q.front();
        q.pop();
    }

    cout << endl;
}