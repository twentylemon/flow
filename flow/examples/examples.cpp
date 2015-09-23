
#include "examples.h"

const std::vector<int> vec14{ 1, 2, 3, 4 };
const std::vector<int> vec58{ 5, 6, 7, 8 };

int main(int argc, char** argv) {
    std::cout << "flow examples" << std::endl << std::endl;

    std::cout << "vec14 = ";
    vec14 | dump();
    std::cout << std::endl << "vec58 = ";
    vec58 | dump();
    std::cout << std::endl;

    concat_example();

    system("pause");
    return 0;
}
