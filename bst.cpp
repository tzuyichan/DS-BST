#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "binary_search_tree.h"

using namespace std;

#define INPUT_MAX_LEN 128

void do_bst_operations(void);
void play_finding_meaty(void);
vector<int> get_input();
vector<int> get_input(string &);
void print(vector<int> &);

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
            // insert
            bst.insert(input);
            break;
        case 'd':
            // delete
            break;
        case 's':
            // search
            break;
        case 'p':
            // print
            break;
        case 'r':
            // call bst destructor
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

    int sword, meaty, trap_idx;
    cout << "Input the filename of the bst map: ";
    cin >> filename;
    // if read file error, return
    input = get_input(filename);
    printf("File has %lu elements\n", input.size());
    print(input);

    cout << "Input the sword's location: ";
    cin >> sword;
    cout << "Input Meaty's location: ";
    cin >> meaty;
    cout << "Input the broccoli traps' index (0~9): ";
    cin >> trap_idx;
    // find meaty
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

vector<int> get_input(string &filename)
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

void print(vector<int> &v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v.at(i) << " ";
    }
    cout << endl;
}