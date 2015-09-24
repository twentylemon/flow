
#include "examples.h"   // defines vec1to4 = {1,2,3,4}, vec5to8 = {5,6,7,8}

void concat_example() {
    std::cout << "flow::concat" << std::endl;

    std::cout << "vec1to4 | concat(vec5to8) = ";
    vec1to4 | concat(vec5to8) | dump(); // 1 2 3 4 5 6 7 8
    std::cout << std::endl;

    std::cout << "vec5to8 | concat(vec1to4) = ";
    vec5to8 | concat(vec1to4) | dump(); // 5 6 7 8 1 2 3 4
    std::cout << std::endl;

    std::cout << " vec1to4 | concat(vec5to8.begin(), vec5to8.begin() + 2) = ";
    vec1to4 | concat(vec5to8.begin(), vec5to8.begin() + 2) | dump();    // 1 2 3 4 5 6
    std::cout << std::endl;

    std::cout << "vec1to4 | limit(2) | concat(vec5to8 | reverse() | limit(2)) = ";
    vec1to4 | limit(2) | concat(vec5to8 | reverse() | limit(2)) | dump();
    // {1 2} + {8 7} = 1 2 8 7
    std::cout << std::endl;
}
