#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define INPUT_MAX_LEN 128

void do_bst_operations(void);
void play_finding_meaty(void);
void parse_input(vector<int> &);

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
        }
    }

    return 0;
}

void do_bst_operations(void)
{
    char op;
    while (true)
    {
        cout << "(i)nsert numbers\n"
                "(d)elete numbers\n"
                "(s)earch for numbers\n"
                "(p)rint 4 kinds of orders\n"
                "(r)eturn"
             << endl;

        cin >> op;

        vector<int> input(INPUT_MAX_LEN);

        switch (op)
        {
        case 'i':
            // insert
            parse_input(input);
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
            return;
        default:
            cout << "Unknown input." << endl;
        }
    }
}

void play_finding_meaty(void)
{
    string map_file;
    int sword, meaty, trap_idx;
    cout << "Input the filename of the bst map: ";
    cin >> map_file;
    // if read file error, return
    cout << "Input the sword's location: ";
    cin >> sword;
    cout << "Input Meaty's location: ";
    cin >> meaty;
    cout << "Input the broccoli traps' index (0~9): ";
    cin >> trap_idx;
    // find meaty
}

void parse_input(vector<int> &input)
{
    cout << "Enter numbers: ";

    int i = 0;
    do
        cin >> input.at(i);
    while (input.at(i++) != -1);

    for (i = 0; input.at(i) != -1; ++i)
    {
        cout << input.at(i) << endl;
    }
}