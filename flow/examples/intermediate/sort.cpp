
#include <examples.h>

void sort_example() {
    std::cout << "flow::sort" << std::endl;

    std::cout << "{ 5, 3, 7, 4, 2, 1, 8, 6 } | sort() = ";
    std::vector<int>{ 5, 3, 7, 4, 2, 1, 8, 6 } | sort() | dump();   // 1 2 3 4 5 6 7 8
    std::cout << std::endl;

    std::cout << "10 random values [0,4] | sort() = ";
    generate([]() { return std::rand() % 5; }, 10) | sort() | dump();   // 0 1 2 2 3 3 4 4 4 4
    std::cout << std::endl << std::endl;
}
