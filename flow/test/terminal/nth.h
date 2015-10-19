
#include "../test.h"

BOOST_AUTO_TEST_CASE(nth_t) {
    BOOST_CHECK_EQUAL(from({ 1 }) | nth(0).value(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | nth(0).value(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | nth(1).value(), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | nth(2).value(), 3);

    BOOST_CHECK_EQUAL(empty<int>() | nth(0).value_or(10), 10);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | nth(4).value_or(10), 10);
}
