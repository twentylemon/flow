
#include <examples.h>

void zip_example() {
    from({ 1, 2, 3, 4 }) | zip({ 1, 2, 3, 4 }) | dump();    // (1, 1) (2, 2) (3, 3) (4, 4)

    from({ 1, 2, 3, 4 }) | zip({ 5, 6, 7, 8 }) | dump();    // (1, 5) (2, 6) (3, 7) (4, 8)

    // the detail zip operation is to create and concatenate tuples,
    // so both the following produce the same stream
    // (1, 1, 1) (2, 2, 2) (3, 3, 3) (4, 4, 4)
    from({ 1, 2, 3, 4 }) | zip({ 1, 2, 3, 4 }) | zip({ 1, 2, 3, 4 }) | dump(); std::cout << std::endl;
    from({ 1, 2, 3, 4 }) | zip(from({ 1, 2, 3, 4 }) | zip({ 1, 2, 3, 4 })) | dump();

    // uncurry() can be used to simplify creating functions for zipped streams
    from({ 1, 2, 3, 4 }) | zip({ 5, 6, 7, 8 })
        | filter(uncurry([](int lhs, int rhs) { return lhs % 2 == 0 && rhs % 4 == 0; })) | dump();  // (4, 8)

    // any zipping operations are possible, such as summing the elements
    from({ 1, 2, 3, 4 }) | zip({ 5, 6, 7, 8 }, std::plus<int>()) | dump();  // 6 8 10 12
}
