
#include "../test.h"

BOOST_AUTO_TEST_CASE(product_noinit) {
    BOOST_CHECK_EQUAL(from({ 1 }) | product().value(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | product().value(), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | product().value(), 6);
    BOOST_CHECK_EQUAL(from({ -1, 2, 3 }) | product().value(), -6);

    BOOST_CHECK_EQUAL(empty<int>() | product().value_or(1), 1);
}

BOOST_AUTO_TEST_CASE(product_init) {
    BOOST_CHECK_EQUAL(from({ 1 }) | product(1), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | product(1), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | product(1), 6);
    BOOST_CHECK_EQUAL(from({ -1, 2, 3 }) | product(1), -6);

    BOOST_CHECK_EQUAL(from({ 1 }) | product(2), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | product(2), 4);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | product(2), 12);
    BOOST_CHECK_EQUAL(from({ -1, 2, 3 }) | product(2), -12);

    BOOST_CHECK_EQUAL(empty<int>() | product(1), 1);
}
