
#include <examples.h>   // defines vec1to4 = {1,2,3,4}, vec5to8 = {5,6,7,8}

void drop_while_example() {
    std::cout << "flow::drop_while" << std::endl;

    std::cout << "vec1to4 | drop_while([](int i) { return i < 2; }) = ";
    vec1to4 | drop_while([](int i) { return i < 2; }) | dump();     // 2 3 4
    std::cout << std::endl;

    std::cout << "vec1to4 | drop_while([](int i) { return i == 0; }) = ";
    vec1to4 | drop_while([](int i) { return i == 0; }) | dump();    // 1 2 3 4
    std::cout << std::endl;

    std::cout << "{1, 2, 1, 1} | drop_while([](int i) { return i == 1; }) = ";
    from({ 1, 2, 1, 1 }) | drop_while([](int i) { return i == 1; }) | dump();   // 2 1 1
    std::cout << std::endl;

    std::cout << "vec1to4 | drop_while([](int i) { return i > 0; }) = ";
    vec1to4 | drop_while([](int i) { return i > 0; }) | dump();     // empty
    std::cout << std::endl << std::endl;
}
