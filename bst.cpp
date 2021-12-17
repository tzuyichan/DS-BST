#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
#include "binary_search_tree.h"

using namespace std;

namespace Text // prompt highlighting
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

/*
 * main loop: enter (1) for bst operations, (2) to play finding Meaty
 */
int main(void)
{
    char mode; // user input game mode
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
            return 0; // end program
        default:
            prompt_bad_input(); // user entered invalid commands
        }
    }

    return 0;
}

/*
 * sub-loop for binary search tree operations (supports repeated operations)
 * operations include: (1) insert, (2) delete, (3) search and (4) print bst
 */
void do_bst_operations(void)
{
    char op; // user input operation
    vector<int> input;
    BST bst; // instantiate binary search tree

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
        case 'i': // insert
            cout << Text::green << "Enter numbers: " << Text::reset;
            input = get_input();   // get input from keyboard
            if (input.size() == 0) // user entered nothing
                continue;
            bst.insert(input);
            break;
        case 'd': // delete
            cout << Text::green << "Enter numbers: " << Text::reset;
            input = get_input();
            if (input.size() == 0)
                continue;
            bst.remove(input);
            break;
        case 's': // search
            cout << Text::green << "Enter numbers: " << Text::reset;
            input = get_input();
            if (input.size() == 0)
                continue;
            bst.find(input);
            break;
        case 'p': // print
            bst.preorder();
            bst.inorder();
            bst.postorder();
            bst.level_order();
            break;
        case 'r':
            return; // back to main menu
        default:
            prompt_bad_input();
        }
    }
}

/*
 * script for playing finding Meaty
 */
void play_finding_meaty(void)
{
    string filename;
    vector<int> input;
    BST bst;
    int sword, meaty, digit;
    queue<int> shortest_path;

    // get filename and file contents
    cout << Text::green << "Input the filename of the bst map: " << Text::reset;
    cin >> filename;
    input = get_input(filename);

    // populate binary search tree
    bst.insert(input);

    // get positions for in game items
    cout << Text::green << "Input the sword's location: " << Text::reset;
    cin >> sword;
    cout << Text::green << "Input Meaty's location: " << Text::reset;
    cin >> meaty;
    cout << Text::green << "Input the broccoli traps' index (0~9): " << Text::reset;
    cin >> digit;

    // remove broccoli traps
    bst.remove(bst.values_containing_digit(digit));
    // find shortest path from root -> sword -> Meaty
    shortest_path = find_shortest_path(bst, sword, meaty);

    // if shortest path exists, print to console
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

/*
 * get user input and return bst initializer
 */
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

/*
 * get file contents and return bst initializer
 */
vector<int> get_input(const string &filename)
{
    string line;

    // read file
    ifstream inFile(filename, ios::in);
    if (!inFile)
    {
        cerr << "Failed to open " << filename << endl;
        exit(EXIT_FAILURE);
    }

    vector<int> input(INPUT_MAX_LEN);

    // get file contents
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

/*
 * find shortest path from root -> sword -> Meaty
 * The path that goes through the sword's and Meaty's lowest common ancestor
 * (LCA) is the shortest path.
 */
queue<int> find_shortest_path(const BST &bst, const int &sword, const int &meaty)
{
    // find path from root -> sword
    BST::Path to_sword = bst.find_path(bst.root_value(), sword);
    queue<int> full_path = to_sword.top_down; // save path to answer

    // find LCA along the path from the sword -> root
    while (!to_sword.bottom_up.empty())
    {
        int lca = to_sword.bottom_up.top();
        to_sword.bottom_up.pop();
        full_path.push(lca); // push the possible LCA in the answer queue

        // try reaching Meaty from this LCA
        BST::Path to_meaty = bst.find_path(lca, meaty);
        // if path exists, save path to answer
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

    return {}; // no path along the path sword -> root goes to Meaty
}

/*
 * remove repeated nodes on the answer path
 * This is a utility function.
 */
queue<int> clean_path(const queue<int> &q)
{
    queue<int> dirty_path = q;
    queue<int> cleaned_path;
    int previous = -1;

    while (!dirty_path.empty())
    {
        // don't include consecutive repeated nodes
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