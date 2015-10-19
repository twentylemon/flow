
#include "../test.h"

BOOST_AUTO_TEST_CASE(first_t) {
    BOOST_CHECK_EQUAL(from({ 1 }) | first().value(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | first().value(), 1);

    BOOST_CHECK_EQUAL(empty<int>() | first().value_or(4), 4);
}
