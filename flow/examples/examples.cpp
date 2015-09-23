
#include "examples.h"

const std::vector<int> vec1to4{ 1, 2, 3, 4 };
const std::vector<int> vec5to8{ 5, 6, 7, 8 };

int main(int argc, char** argv) {
    std::cout << "flow examples" << std::endl << std::endl;

    std::cout << "vec1to4 = ";
    vec1to4 | dump();
    std::cout << std::endl << "vec5to8 = ";
    vec5to8 | dump();
    std::cout << std::endl;

    concat_example();

    system("pause");
    return 0;
}
