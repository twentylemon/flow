
#include "../test.h"

BOOST_AUTO_TEST_CASE(contains_t) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | contains(1), true);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | contains(2), true);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | contains(3), true);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | contains(0), false);
    BOOST_CHECK_EQUAL(from({ 1 }) | contains(1), true);
    BOOST_CHECK_EQUAL(from({ 1 }) | contains(0), false);
    BOOST_CHECK_EQUAL(empty<int>() | contains(0), false);

    auto s = from({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL(s | contains(1), true);
    BOOST_CHECK_EQUAL(s | contains(2), true);
    BOOST_CHECK_EQUAL(s | contains(3), true);
    BOOST_CHECK_EQUAL(s | contains(4), false);
}
