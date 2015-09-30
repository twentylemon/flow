
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_terminal)

BOOST_AUTO_TEST_CASE(min_less) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | min(), 1);
    BOOST_CHECK_EQUAL(from({ 3, 2, 1 }) | min(), 1);
    BOOST_CHECK_EQUAL(from({ 3, 1, 2 }) | min(), 1);
    BOOST_CHECK_EQUAL(from({ 3, 3, 3 }) | min(), 3);
    BOOST_CHECK_EQUAL(from({ 2, 2, 3 }) | min(), 2);
    BOOST_CHECK_EQUAL(from({ 3 }) | min(), 3);

    BOOST_CHECK_THROW(empty<int>() | min(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(min_comp) {
    BOOST_CHECK_EQUAL(from({ -4, 3, 2 }) | min(square_less), 2);
    BOOST_CHECK_EQUAL(from({ 2, 3, -4 }) | min(square_less), 2);
    BOOST_CHECK_EQUAL(from({ -4, 2, 3 }) | min(square_less), 2);
    BOOST_CHECK_EQUAL(from({ 2, -4, 2, 3 }) | min(square_less), 2);
    BOOST_CHECK_EQUAL(from({ 4, -4, -4 }) | min(square_less), 4);
    BOOST_CHECK_EQUAL(from({ 3 }) | min(square_less), 3);

    BOOST_CHECK_THROW(empty<int>() | min(square_less), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
