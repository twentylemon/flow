
#include "../test.h"

BOOST_AUTO_TEST_CASE(count_t) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(), 3);
    BOOST_CHECK_EQUAL(empty<int>() | count(), 0);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | filter(is_even) | count(), 1);
}

BOOST_AUTO_TEST_CASE(count_if_t) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count_if([](int i) { return i < 4; }), 3);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count_if([](int i) { return i < 3; }), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count_if([](int i) { return i < 2; }), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count_if([](int i) { return i < 1; }), 0);
    BOOST_CHECK_EQUAL(from({ 1 }) | count_if([](int i) { return i > 0; }), 1);
    BOOST_CHECK_EQUAL(from({ 0 }) | count_if([](int i) { return i > 0; }), 0);
    BOOST_CHECK_EQUAL(empty<int>() | count_if([](int i) { return true; }), 0);
}

BOOST_AUTO_TEST_CASE(count_val_t) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(1), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(2), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(3), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(0), 0);
    BOOST_CHECK_EQUAL(from({ 1 }) | count(1), 1);
    BOOST_CHECK_EQUAL(from({ 1 }) | count(0), 0);
    BOOST_CHECK_EQUAL(empty<int>() | count(0), 0);
}
