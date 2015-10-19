
#include "../test.h"

BOOST_AUTO_TEST_CASE(max_less) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | max().value(), 3);
    BOOST_CHECK_EQUAL(from({ 3, 2, 1 }) | max().value(), 3);
    BOOST_CHECK_EQUAL(from({ 1, 3, 2 }) | max().value(), 3);
    BOOST_CHECK_EQUAL(from({ 3, 3, 3 }) | max().value(), 3);
    BOOST_CHECK_EQUAL(from({ 3, 2, 3 }) | max().value(), 3);
    BOOST_CHECK_EQUAL(from({ 3 }) | max().value(), 3);

    BOOST_CHECK_EQUAL(empty<int>() | max().value_or(-1), -1);
}

BOOST_AUTO_TEST_CASE(max_comp) {
    BOOST_CHECK_EQUAL(from({ -4, 3, 2 }) | max(square_less).value(), -4);
    BOOST_CHECK_EQUAL(from({ 2, 3, -4 }) | max(square_less).value(), -4);
    BOOST_CHECK_EQUAL(from({ 2, -4, 3 }) | max(square_less).value(), -4);
    BOOST_CHECK_EQUAL(from({ 2, -4, -4, 3 }) | max(square_less).value(), -4);
    BOOST_CHECK_EQUAL(from({ -4, 4, 4 }) | max(square_less).value(), -4);
    BOOST_CHECK_EQUAL(from({ 3 }) | max(square_less).value(), 3);

    BOOST_CHECK_EQUAL(empty<int>() | max(square_less).value_or(-1), -1);
}
