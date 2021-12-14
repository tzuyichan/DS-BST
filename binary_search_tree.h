#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <vector>
#include <queue>
#include <stack>

using namespace std;

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
    struct Path
    {
        queue<int> top_down;
        stack<int> bottom_up;
    };

    BST();
    ~BST();
    int root_value() const;
    void insert(const int &);
    void insert(const vector<int> &);
    void remove(const int &);
    void remove(const vector<int> &);
    void find(const vector<int> &);
    Path find_path(const int &, const int &) const;
    vector<int> values_containing_digit(const int &);
    void inorder();
    void preorder();
    void postorder();
    queue<int> get_postorder() const;
    void level_order();

private:
    Node *root;
    Search_result find(const int &) const;
    Search_result find_next_larger_than(Node *);
    void inorder(Node *);
    void preorder(Node *);
    void postorder(Node *);
    void postorder(Node *, queue<int> &) const;
    void destruct_tree(Node *);
};

#endif