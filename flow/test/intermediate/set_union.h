
#include "../test.h"

BOOST_AUTO_TEST_CASE(set_union_t) {
    std::vector<int> v1 = { 1, 3, 5, 7 };
    std::vector<int> v2 = { 2, 4, 6, 8 };

    std::vector<int> ex = { 1, 2, 3, 4, 5, 6, 7, 8 };
    auto s = v1 | set_union(v2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 1 };
    s = from({ 1, 1 }) | set_union({ 1 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 1, 2, 2 };
    s = from({ 1, 1, 2 }) | set_union({ 1, 2, 2 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    v1 = { 1, 2, 3 };
    v2 = { 4, 5, 6 };
    ex = { 1, 2, 3, 4, 5, 6 };
    s = v1 | set_union(v2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3 };
    s = v1 | set_union(v1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3, 4, 5 };
    s = v1 | set_union(v2.begin(), v2.begin() + 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3 };
    s = v1 | set_union(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    s = empty<int>() | set_union(v1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { -1, 2, -3, -4, 5 };
    s = from({ 2, -4, 5 }) | set_union({ -1, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, -2, 3 };
    s = from({ 1, -2, 3 }) | set_union({ -1, 2, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = empty<int>() | set_union(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}
