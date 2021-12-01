#include <iostream>
#include <vector>

using namespace std;

void do_bst_operations(void);
void play_finding_meaty(void);

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

        switch (op)
        {
        case 'i':
            // insert
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
}