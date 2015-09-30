
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_terminal)

BOOST_AUTO_TEST_CASE(max_less) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | max(), 3);
    BOOST_CHECK_EQUAL(from({ 3, 2, 1 }) | max(), 3);
    BOOST_CHECK_EQUAL(from({ 1, 3, 2 }) | max(), 3);
    BOOST_CHECK_EQUAL(from({ 3, 3, 3 }) | max(), 3);
    BOOST_CHECK_EQUAL(from({ 3, 2, 3 }) | max(), 3);
    BOOST_CHECK_EQUAL(from({ 3 }) | max(), 3);

    BOOST_CHECK_THROW(empty<int>() | max(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(max_comp) {
    BOOST_CHECK_EQUAL(from({ -4, 3, 2 }) | max(square_less), -4);
    BOOST_CHECK_EQUAL(from({ 2, 3, -4 }) | max(square_less), -4);
    BOOST_CHECK_EQUAL(from({ 2, -4, 3 }) | max(square_less), -4);
    BOOST_CHECK_EQUAL(from({ 2, -4, -4, 3 }) | max(square_less), -4);
    BOOST_CHECK_EQUAL(from({ -4, 4, 4 }) | max(square_less), -4);
    BOOST_CHECK_EQUAL(from({ 3 }) | max(square_less), 3);

    BOOST_CHECK_THROW(empty<int>() | max(square_less), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
