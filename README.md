# Binary Search Tree
* contributed by < `詹子毅 F04066028` >
* course: [NCKU Data Structures 2021](http://class-qry.acad.ncku.edu.tw/syllabus/online_display.php?syear=0110&sem=1&co_no=F720300&class_code=2)
* course instructor: Prof. Tseng, Fan-Hsun

## Configuration
* language: C++11
* environment: VS Code, MacOS Terminal
* compiler: Apple LLVM version 10.0.1 (clang-1001.0.46.4)

## Build
If you are using `clang 3.3` or above, simply run
```
$ make
```
If you are using `gcc 4.8.1` or above, run
```
$ make gcc
```
Finally, run `bst` with
```
$ ./bst
```
Make sure `bstmap.txt` is included in the same directory.

## Program Structure
#### `bst.cpp`
```c
#include <bst data structure>

while (true)
{
    cin >> game mode;
    switch (game mode)
    {
    case 'bst operations':
        BST bst;
        // do bst operations
        while (operation)
        {
            operation = insert || delete || search || print;
            // execute operation
        }
    case 'finding Meaty':
        BST bst;
        // play finding Meaty
        cout << bst.shortest_path();
    }
}
```