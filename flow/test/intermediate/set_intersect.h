
#include "../test.h"

BOOST_AUTO_TEST_CASE(set_intersect_t) {
    std::vector<int> v1 = { 1, 3, 5, 7 };
    std::vector<int> v2 = { 1, 2, 3, 4 };

    std::vector<int> ex = { 1, 3 };
    auto s = v1 | set_intersect(v2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2 };
    s = from({ 1, 1, 2 }) | set_intersect({ 1, 2, 2 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 3, 5, 7 };
    s = v1 | set_intersect(v1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 3 };
    s = v1 | set_intersect(v1.begin(), v1.begin() + 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = v1 | set_intersect(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    s = empty<int>() | set_intersect(v1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = from({ 2, -4, 5 }) | set_intersect({ -1, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, -2, 3 };
    s = from({ 1, 1, -2, 3 }) | set_intersect({ -1, 2, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = empty<int>() | set_intersect(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}
