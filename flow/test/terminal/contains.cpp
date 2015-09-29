
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_terminal)

BOOST_AUTO_TEST_CASE(contains_t) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | contains(1), true);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | contains(2), true);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | contains(3), true);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | contains(0), false);
    BOOST_CHECK_EQUAL(from({ 1 }) | contains(1), true);
    BOOST_CHECK_EQUAL(from({ 1 }) | contains(0), false);
    BOOST_CHECK_EQUAL(empty<int>() | contains(0), false);
}

BOOST_AUTO_TEST_SUITE_END()
