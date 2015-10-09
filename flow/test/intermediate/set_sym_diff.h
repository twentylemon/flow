
#include "../test.h"

BOOST_AUTO_TEST_CASE(set_sym_diff_t) {
    std::vector<int> v1 = { 1, 3, 5, 7 };
    std::vector<int> v2 = { 1, 2, 3, 4 };

    std::vector<int> ex = { 2, 4, 5, 7 };
    auto s = v1 | set_sym_diff(v2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2 };
    s = from({ 1, 1, 2 }) | set_sym_diff({ 1, 2, 2 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 1, 2, 2 };
    s = from({ 1, 1, 1 }) | set_sym_diff({ 1, 2, 2 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = v1 | set_sym_diff(v1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 5, 7 };
    s = v1 | set_sym_diff(v1.begin(), v1.begin() + 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 3, 5, 7 };
    s = v1 | set_sym_diff(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 3, 5, 7 };
    s = empty<int>() | set_sym_diff(v1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, -4, 5 };
    s = from({ 2, -4, 5 }) | set_sym_diff({ 1, -2 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1 };
    s = from({ 1, 1, -2, 3 }) | set_sym_diff({ -1, 2, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = from({ 1, -2, 3 }) | set_sym_diff({ -1, 2, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = empty<int>() | set_sym_diff(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}
