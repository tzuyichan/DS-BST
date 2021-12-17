#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
#include "binary_search_tree.h"

using namespace std;

namespace Text
{
    const string green = "\033[0;32m";
    const string yellow = "\033[0;33m";
    const string red = "\033[0;31m";
    const string reset = "\033[0m";
}

extern const int INPUT_MAX_LEN = 128;

void do_bst_operations(void);
void play_finding_meaty(void);
vector<int> get_input();
vector<int> get_input(const string &);
void prompt_bad_input(void);
queue<int> find_shortest_path(const BST &, const int &, const int &);
queue<int> clean_path(const queue<int> &);
void print(const vector<int> &);
void print(const queue<int> &);
void print(const stack<int> &);

int main(void)
{
    char mode;
    while (true)
    {
        cout << Text::green
             << "(1) Binary search tree\n"
                "(2) Finding Meaty\n"
                "(0) Exit"
             << Text::reset << endl;
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
            prompt_bad_input();
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
        cout << Text::green
             << "(i)nsert numbers\n"
                "(d)elete numbers\n"
                "(s)earch for numbers\n"
                "(p)rint 4 kinds of orders\n"
                "(r)eturn"
             << Text::reset << endl;
        cin >> op;

        switch (op)
        {
        case 'i':
            cout << Text::green << "Enter numbers: " << Text::reset;
            input = get_input();
            if (input.size() == 0)
                continue;
            bst.insert(input);
            break;
        case 'd':
            cout << Text::green << "Enter numbers: " << Text::reset;
            input = get_input();
            if (input.size() == 0)
                continue;
            bst.remove(input);
            break;
        case 's':
            cout << Text::green << "Enter numbers: " << Text::reset;
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
            prompt_bad_input();
        }
    }
}

void play_finding_meaty(void)
{
    string filename;
    vector<int> input;
    BST bst;
    int sword, meaty, digit;
    queue<int> shortest_path;

    cout << Text::green << "Input the filename of the bst map: " << Text::reset;
    cin >> filename;
    input = get_input(filename);

    bst.insert(input);

    cout << Text::green << "Input the sword's location: " << Text::reset;
    cin >> sword;
    cout << Text::green << "Input Meaty's location: " << Text::reset;
    cin >> meaty;
    cout << Text::green << "Input the broccoli traps' index (0~9): " << Text::reset;
    cin >> digit;

    bst.remove(bst.values_containing_digit(digit));
    shortest_path = find_shortest_path(bst, sword, meaty);

    if (!shortest_path.empty())
    {
        cout << Text::yellow
             << "Capoo found Meaty!\n"
                "The shortest path to Meaty is:"
             << Text::reset << endl;
        print(shortest_path);
    }
    else
    {
        cout << Text::red << "No valid path." << Text::reset << endl;
    }
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

    cout << Text::yellow << "Load file success." << Text::reset << endl;
    return input;
}

void prompt_bad_input(void)
{
    cout << Text::red << "Unknown input." << Text::reset << endl;
    cin.clear();
    cin.ignore(INT32_MAX, '\n');
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

void print(const stack<int> &s)
{
    stack<int> path = s;
    while (!path.empty())
    {
        cout << path.top() << " ";
        path.pop();
    }
    cout << endl;
}