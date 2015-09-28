
#include <examples.h>   // defines vec1to4 = {1,2,3,4}, vec5to8 = {5,6,7,8}

void zip_example() {
    std::cout << "flow::zip" << std::endl;

    std::cout << "vec1to4 | zip(vec1to4) = ";
    vec1to4 | zip(vec1to4) | dump();    // (1, 1) (2, 2) (3, 3) (4, 4)
    std::cout << std::endl;

    std::cout << "vec1to4 | zip(vec5to8) = ";
    vec1to4 | zip(vec5to8) | dump();    // (1, 5) (2, 6) (3, 7) (4, 8)
    std::cout << std::endl;

    // the detail zip operation is to create and concatenate tuples,
    // so both the following produce the same stream
    // (1, 1, 1) (2, 2, 2) (3, 3, 3) (4, 4, 4)
    vec1to4 | zip(vec1to4) | zip(vec1to4) | dump(); std::cout << std::endl;
    vec1to4 | zip(vec1to4 | zip(vec1to4)) | dump();
    std::cout << std::endl;

    // uncurry() can be used to simplify creating functions for zipped streams
    std::cout << "vec1to4 | zip(vec5to8) | filter(uncurry([](int lhs, int rhs) { return lhs % 2 == 0 && rhs % 4 == 0; })) = ";
    vec1to4 | zip(vec5to8) | filter(uncurry([](int lhs, int rhs) { return lhs % 2 == 0 && rhs % 4 == 0; })) | dump();   // (4, 8)
    std::cout << std::endl;

    // other zipping operations are possible, such as summing the elements
    std::cout << "vec1to4 | zip(vec5to8, std::plus<int>()) = ";
    vec1to4 | zip(vec5to8, std::plus<int>()) | dump();  // 6 8 10 12

    std::cout << std::endl << std::endl;
}
