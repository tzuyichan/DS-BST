#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

#define INPUT_MAX_LEN 128

void do_bst_operations(void);
void play_finding_meaty(void);
int get_input(vector<int> &);
int get_input(vector<int> &, string &);
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
        int count;

        switch (op)
        {
        case 'i':
            if ((count = get_input(input)) == 0)
                continue;
            // insert
            printf("do insert elements\n");
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
    string filename;
    vector<int> input(INPUT_MAX_LEN);
    int count;

    int sword, meaty, trap_idx;
    cout << "Input the filename of the bst map: ";
    cin >> filename;
    // if read file error, return
    count = get_input(input, filename);
    printf("File has %d elements\n", count);

    cout << "Input the sword's location: ";
    cin >> sword;
    cout << "Input Meaty's location: ";
    cin >> meaty;
    cout << "Input the broccoli traps' index (0~9): ";
    cin >> trap_idx;
    // find meaty
}

int get_input(vector<int> &input)
{
    cout << "Enter numbers: ";

    int i = 0;
    do
        cin >> input.at(i);
    while (input.at(i++) != -1);

    return i - 1;
}

int get_input(vector<int> &input, string &filename)
{
    string line;

    // Read file.
    ifstream inFile(filename, ios::in);
    if (!inFile)
    {
        cerr << "Failed to open " << filename << endl;
        exit(EXIT_FAILURE); // exit program if failed to read file
    }

    int i = 0;
    while (getline(inFile, line))
    {
        input.at(i++) = stoi(line);
    }
    input.at(i) = -1;

    print(input);

    return i;
}

void print(vector<int> &v)
{
    for (int i = 0; v.at(i) != -1; ++i)
    {
        cout << v.at(i) << " ";
    }
    cout << endl;
}