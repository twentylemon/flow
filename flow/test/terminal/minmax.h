
#include "../test.h"

BOOST_AUTO_TEST_CASE(minmax_less) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | minmax().value(), std::make_pair(1, 3));
    BOOST_CHECK_EQUAL(from({ 3, 2, 1 }) | minmax().value(), std::make_pair(1, 3));
    BOOST_CHECK_EQUAL(from({ 3, 1, 2 }) | minmax().value(), std::make_pair(1, 3));
    BOOST_CHECK_EQUAL(from({ 3, 3, 3 }) | minmax().value(), std::make_pair(3, 3));
    BOOST_CHECK_EQUAL(from({ 2, 2, 3 }) | minmax().value(), std::make_pair(2, 3));
    BOOST_CHECK_EQUAL(from({ 3 }) | minmax().value(), std::make_pair(3, 3));

    BOOST_CHECK_EQUAL(empty<int>() | minmax().value_or(std::make_pair(-1, -1)), std::make_pair(-1, -1));
}

BOOST_AUTO_TEST_CASE(minmax_comp) {
    BOOST_CHECK_EQUAL(from({ -4, 3, 2 }) | minmax(square_less).value(), std::make_pair(2, -4));
    BOOST_CHECK_EQUAL(from({ 2, 3, -4 }) | minmax(square_less).value(), std::make_pair(2, -4));
    BOOST_CHECK_EQUAL(from({ -4, 2, 3 }) | minmax(square_less).value(), std::make_pair(2, -4));
    BOOST_CHECK_EQUAL(from({ 2, -4, 4, -2, 3 }) | minmax(square_less).value(), std::make_pair(2, 4));
    BOOST_CHECK_EQUAL(from({ 4, -4, -4 }) | minmax(square_less).value(), std::make_pair(4, 4));
    BOOST_CHECK_EQUAL(from({ 2, 4, -4, -4 }) | minmax(square_less).value(), std::make_pair(2, -4));
    BOOST_CHECK_EQUAL(from({ 3 }) | minmax(square_less).value(), std::make_pair(3, 3));

    BOOST_CHECK_EQUAL(empty<int>() | minmax(square_less).value_or(std::make_pair(-1, -1)), std::make_pair(-1, -1));
}
