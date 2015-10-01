
#include "../test.h"

BOOST_AUTO_TEST_CASE(count_t) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(), 3);
    BOOST_CHECK_EQUAL(empty<int>() | count(), 0);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | filter(is_even) | count(), 1);
}
