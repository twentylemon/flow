
#include "examples.h"

const std::vector<int> vec1to4 = iota(1) | limit(4) | to_vector();
const std::vector<int> vec5to8 = iota(5) | limit(4) | to_vector();
const std::vector<int> vec1to8 = iota(1) | limit(8) | to_vector();

int main(int argc, char** argv) {
    std::cout << "flow examples" << std::endl << std::endl;

    std::cout << "vec1to4 = ";
    vec1to4 | dump();
    std::cout << std::endl << "vec5to8 = ";
    vec5to8 | dump();
    std::cout << std::endl;

    concat_example();

    cycle(vec1to4, 1) | dump();

    system("pause");
    return 0;
}
