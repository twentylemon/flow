
#include "test.h"

BOOST_AUTO_TEST_CASE(lazy_t) {
    std::vector<int> s = { 1, 2, 3 };
    auto f = [](int i) { return i > 2; };
    auto f_inv = [](int i) { return i <= 2; };

    BOOST_CHECK_EQUAL(s | count(), s.size());
    BOOST_CHECK_EQUAL(s | filter(f) | count(), 1);
    BOOST_CHECK_EQUAL(s | filter(f) | count(3), 1);
    BOOST_CHECK_EQUAL(s | filter(f) | count(2), 0);

    BOOST_CHECK_EQUAL(s | drop_while(f) | count(), 3);
    BOOST_CHECK_EQUAL(s | drop_while(f) | count(1), 1);
    BOOST_CHECK_EQUAL(s | drop_while(f) | count(2), 1);
    BOOST_CHECK_EQUAL(s | drop_while(f) | count(3), 1);
    BOOST_CHECK_EQUAL(s | drop_while(f) | count(4), 0);

    BOOST_CHECK_EQUAL(s | take_while(f) | count(), 0);
    BOOST_CHECK_EQUAL(s | take_while(f) | count(1), 0);
    BOOST_CHECK_EQUAL(s | take_while(f) | count(2), 0);
    BOOST_CHECK_EQUAL(s | take_while(f) | count(3), 0);

    BOOST_CHECK_EQUAL(s | take_while(f_inv) | count(), 2);
    BOOST_CHECK_EQUAL(s | take_while(f_inv) | count(1), 1);
    BOOST_CHECK_EQUAL(s | take_while(f_inv) | count(2), 1);
    BOOST_CHECK_EQUAL(s | take_while(f_inv) | count(3), 0);

    BOOST_CHECK_EQUAL(s | flat_map([](int i) { return repeat(i, i); }) | count(), 1 + 2 + 3);
    BOOST_CHECK_EQUAL(s | flat_map([](int i) { return repeat(i, i); }) | count(1), 1);
    BOOST_CHECK_EQUAL(s | flat_map([](int i) { return repeat(i, i); }) | count(2), 2);
    BOOST_CHECK_EQUAL(s | flat_map([](int i) { return repeat(i, i); }) | count(3), 3);
    BOOST_CHECK_EQUAL(s | flat_map([](int i) { return repeat(i, i); }) | count(4), 0);

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | merge({ 1, 2, 3 }) | count(), 6);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | merge({ 1, 2, 3 }) | count(1), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | merge({ 1, 2, 3 }) | count(2), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | merge({ 1, 2, 3 }) | count(3), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | merge({ 1, 2, 3 }) | count(4), 0);

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | set_union({ 1, 2, 3 }) | count(), 3);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | set_union({ 1, 2, 3 }) | count(1), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | set_union({ 1, 2, 3 }) | count(2), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | set_union({ 1, 2, 3 }) | count(3), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | set_union({ 1, 2, 3 }) | count(4), 0);
    // all set opts should be fine when these pass; they are all the same class

    BOOST_CHECK_EQUAL(s | flat_map([](int i) { return repeat(i, i); }) | filter(is_even) | count(), 2);
    BOOST_CHECK_EQUAL(s | flat_map([](int i) { return repeat(i, i); }) | take_while(f_inv) | count(), 1 + 2);
    BOOST_CHECK_EQUAL(s | flat_map([](int i) { return repeat(i, i); }) | drop_while(f_inv) | count(), 3);
}
