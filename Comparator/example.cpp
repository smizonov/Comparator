#include <comparator.h>
#include <iostream>
int main()
{
    std::string path1, path2;
    std::cout << "This program help find the same files in directories!\n"
              << "Enter path to first directory: ";
    std::cin >> path1;
    std::cout << "\nEnter path to second directory: ";
    std::cin >> path2;
    Answer ans(compare_manager(path1, path2));
    print_answer(ans, path1, path2);
}

