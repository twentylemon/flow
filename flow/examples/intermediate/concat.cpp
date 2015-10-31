
#include <examples.h>

void concat_example() {
    from({ 1, 2, 3, 4 }) | concat({ 5, 6, 7, 8 }) | dump(); // 1 2 3 4 5 6 7 8

    from({ 5, 6, 7, 8 }) | concat({ 1, 2, 3, 4 }) | dump(); // 5 6 7 8 1 2 3 4

    from({ 1, 2, 3, 4 }) | concat(from({ 1, 2, 3, 4 }) | limit(2)) | dump();    // 1 2 3 4 5 6

    from({ 1, 2, 3, 4 }) | limit(2) | concat(from({ 5, 6, 7, 8 }) | reverse() | limit(2)) | dump(); // {1 2} + {8 7} = 1 2 8 7
}
