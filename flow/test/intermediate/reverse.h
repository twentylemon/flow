
#include "../test.h"

BOOST_AUTO_TEST_CASE(reverse_t) {
    std::vector<int> ex = { 3, 2, 1 };
    auto s = from({ 1, 2, 3 }) | reverse() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | reverse() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1 };
    s = from({ 1 }) | reverse() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}
