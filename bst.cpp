#include <iostream>
#include <vector>

int main(void)
{
    std::cout << "Hello world!" << std::endl;
    std::vector<int> v = {1, 2, 3, 4, 5};
    for (auto i : v)
        std::cout << i << " " << std::endl;
    return 0;
}