
#include "../test.h"

BOOST_AUTO_TEST_CASE(replace_map_t) {
    std::vector<int> ex = { 1, -2, 3 };
    auto s = from({ 1, 2, 3 }) | replace_map(is_even, negate) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | replace_map(is_even, negate) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 1 };
    s = from({ 1, 1, 1 }) | replace_map(is_even, negate) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { -2, -2, 2 };
    s = from({ 2, 2, -2 }) | replace_map(is_even, negate) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_CASE(replace_val) {
    std::vector<int> ex = { 3, 2, 3 };
    auto s = from({ 1, 2, 3 }) | replace(1, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 2, 3 };
    s = from({ 1, 2, 3 }) | replace(0, 5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | replace(0, 1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 2, 2, 2 };
    s = from({ 1, 1, 1 }) | replace(1, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_CASE(replace_pred) {
    std::vector<int> ex = { 1, 3, 3 };
    auto s = from({ 1, 2, 3 }) | replace(is_even, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | replace(is_even, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 1 };
    s = from({ 1, 1, 1 }) | replace(is_even, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 3, 3, 3 };
    s = from({ 2, 2, 2 }) | replace(is_even, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}
