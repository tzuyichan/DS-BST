#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
#include "binary_search_tree.h"

using namespace std;

#define INPUT_MAX_LEN 128

void do_bst_operations(void);
void play_finding_meaty(void);
vector<int> get_input();
vector<int> get_input(const string &);
vector<int> find_vals_containing_digit(const int &, const BST &);
queue<int> find_shortest_path(const BST &, const int &, const int &);
queue<int> clean_path(const queue<int> &);
void print(const vector<int> &);
void print(const queue<int> &);

int main(void)
{
    char mode;
    while (true)
    {
        cout << "(1) Binary search tree\n"
                "(2) Finding Meaty\n"
                "(0) Exit"
             << endl;
        cin >> mode;

        switch (mode)
        {
        case '1':
            do_bst_operations();
            break;
        case '2':
            play_finding_meaty();
            break;
        case '0':
            return 0;
        default:
            cout << "Unknown input." << endl;
            cin.clear();
            cin.ignore(INT32_MAX, '\n');
        }
    }

    return 0;
}

void do_bst_operations(void)
{
    char op;
    vector<int> input;
    BST bst;

    while (true)
    {
        cout << "(i)nsert numbers\n"
                "(d)elete numbers\n"
                "(s)earch for numbers\n"
                "(p)rint 4 kinds of orders\n"
                "(r)eturn"
             << endl;
        cin >> op;

        switch (op)
        {
        case 'i':
            cout << "Enter numbers: ";
            input = get_input();
            if (input.size() == 0)
                continue;
            bst.insert(input);
            break;
        case 'd':
            cout << "Enter numbers: ";
            input = get_input();
            if (input.size() == 0)
                continue;
            bst.remove(input);
            break;
        case 's':
            cout << "Enter numbers: ";
            input = get_input();
            if (input.size() == 0)
                continue;
            bst.find(input);
            break;
        case 'p':
            bst.preorder();
            bst.inorder();
            bst.postorder();
            bst.level_order();
            break;
        case 'r':
            return;
        default:
            cout << "Unknown input." << endl;
            cin.clear();
            cin.ignore(INT32_MAX, '\n');
        }
    }
}

void play_finding_meaty(void)
{
    string filename;
    vector<int> input;
    BST bst;

    int sword, meaty, digit;
    cout << "Input the filename of the bst map: ";
    cin >> filename;
    input = get_input(filename);
    bst.insert(input);

    cout << "Input the sword's location: ";
    cin >> sword;
    cout << "Input Meaty's location: ";
    cin >> meaty;
    cout << "Input the broccoli traps' index (0~9): ";
    cin >> digit;
    // find meaty
    bst.remove(find_vals_containing_digit(digit, bst));
    print(find_shortest_path(bst, sword, meaty));
}

vector<int> get_input()
{
    vector<int> input(INPUT_MAX_LEN);

    int i = 0;
    do
        cin >> input.at(i);
    while (input.at(i++) != -1);

    if (input.at(0) == -1)
        return {};
    else
    {
        input.resize(i - 1);
        return input;
    }
}

vector<int> get_input(const string &filename)
{
    string line;

    // Read file.
    ifstream inFile(filename, ios::in);
    if (!inFile)
    {
        cerr << "Failed to open " << filename << endl;
        exit(EXIT_FAILURE);
    }

    vector<int> input(INPUT_MAX_LEN);

    int i = 0;
    while (getline(inFile, line))
    {
        input.at(i++) = stoi(line);
    }
    input.resize(i);

    return input;
}

vector<int> find_vals_containing_digit(const int &x, const BST &bst)
{
    vector<int> to_be_deleted(INPUT_MAX_LEN);
    int delete_cnt = 0;

    queue<int> postorder_bst = bst.get_postorder();

    while (!postorder_bst.empty())
    {
        string value = to_string(postorder_bst.front());
        postorder_bst.pop();

        if (value.find(to_string(x)) != -1)
        {
            to_be_deleted.at(delete_cnt++) = stoi(value);
        }
    }
    to_be_deleted.resize(delete_cnt);

    return to_be_deleted;
}

queue<int> find_shortest_path(const BST &bst, const int &sword, const int &meaty)
{
    BST::Path to_sword = bst.find_path(bst.root_value(), sword);
    queue<int> full_path = to_sword.top_down;

    while (!to_sword.bottom_up.empty())
    {
        int lca = to_sword.bottom_up.top();
        to_sword.bottom_up.pop();
        full_path.push(lca);
        BST::Path to_meaty = bst.find_path(lca, meaty);

        if (!to_meaty.top_down.empty())
        {
            while (!to_meaty.top_down.empty())
            {
                full_path.push(to_meaty.top_down.front());
                to_meaty.top_down.pop();
            }

            return clean_path(full_path);
        }
    }

    return {};
}

queue<int> clean_path(const queue<int> &q)
{
    queue<int> dirty_path = q;
    queue<int> cleaned_path;
    int previous = -1;

    while (!dirty_path.empty())
    {
        if (dirty_path.front() != previous)
        {
            cleaned_path.push(dirty_path.front());
        }
        previous = dirty_path.front();
        dirty_path.pop();
    }

    return cleaned_path;
}

void print(const vector<int> &v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v.at(i) << " ";
    }
    cout << endl;
}

void print(const queue<int> &q)
{
    queue<int> bst = q;
    while (!bst.empty())
    {
        cout << bst.front() << " ";
        bst.pop();
    }
    cout << endl;
}