
#include <examples.h>

void drop_while_example() {
    from({ 1, 2, 3, 4 }) | drop_while([](int i) { return i < 2; }) | dump();    // 2 3 4

    from({ 1, 2, 3, 4 }) | drop_while([](int i) { return i == 0; }) | dump();   // 1 2 3 4

    from({ 1, 2, 1, 1 }) | drop_while([](int i) { return i == 1; }) | dump();   // 2 1 1

    from({ 1, 2, 3, 4 }) | drop_while([](int i) { return i > 0; }) | dump();    // empty
}
