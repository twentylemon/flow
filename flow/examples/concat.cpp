
#include "examples.h"   // defines vec14 = {1,2,3,4}, vec58 = {5,6,7,8}

void concat_example() {
    std::cout << "flow::concat" << std::endl;

    std::cout << "vec14 | concat(vec58) = ";
    vec14 | concat(vec58) | dump(); // 1 2 3 4 5 6 7 8
    std::cout << std::endl;

    std::cout << "vec58 | concat(vec14) = ";
    vec58 | concat(vec14) | dump(); // 5 6 7 8 1 2 3 4
    std::cout << std::endl;

    std::cout << "vec14 | limit(2) | concat(vec58 | reverse() | limit(2)) = ";
    vec14 | limit(2) | concat(vec58 | reverse() | limit(2)) | dump();
    // {1 2} + {8 7} = 1 2 8 7
    std::cout << std::endl;
}
