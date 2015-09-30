
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_terminal)

BOOST_AUTO_TEST_CASE(nth_t) {
    BOOST_CHECK_EQUAL(from({ 1 }) | nth(0), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | nth(0), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | nth(1), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | nth(2), 3);

    BOOST_CHECK_THROW(empty<int>() | nth(0), std::out_of_range);
    BOOST_CHECK_THROW(from({ 1, 2, 3 }) | nth(4), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
