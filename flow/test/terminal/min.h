
#include "../test.h"

BOOST_AUTO_TEST_CASE(min_less) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | min().value(), 1);
    BOOST_CHECK_EQUAL(from({ 3, 2, 1 }) | min().value(), 1);
    BOOST_CHECK_EQUAL(from({ 3, 1, 2 }) | min().value(), 1);
    BOOST_CHECK_EQUAL(from({ 3, 3, 3 }) | min().value(), 3);
    BOOST_CHECK_EQUAL(from({ 2, 2, 3 }) | min().value(), 2);
    BOOST_CHECK_EQUAL(from({ 3 }) | min().value(), 3);

    BOOST_CHECK_EQUAL(empty<int>() | min().value_or(-1), -1);
}

BOOST_AUTO_TEST_CASE(min_comp) {
    BOOST_CHECK_EQUAL(from({ -4, 3, 2 }) | min(square_less).value(), 2);
    BOOST_CHECK_EQUAL(from({ 2, 3, -4 }) | min(square_less).value(), 2);
    BOOST_CHECK_EQUAL(from({ -4, 2, 3 }) | min(square_less).value(), 2);
    BOOST_CHECK_EQUAL(from({ 2, -4, 2, 3 }) | min(square_less).value(), 2);
    BOOST_CHECK_EQUAL(from({ 4, -4, -4 }) | min(square_less).value(), 4);
    BOOST_CHECK_EQUAL(from({ 3 }) | min(square_less).value(), 3);

    BOOST_CHECK_EQUAL(empty<int>() | min(square_less).value_or(-1), -1);
}
