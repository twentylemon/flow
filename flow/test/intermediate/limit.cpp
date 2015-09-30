
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_intermediate)

BOOST_AUTO_TEST_CASE(limit_t) {
    std::vector<int> vec = { 1, 2, 3, 4, 5, 6 };

    std::vector<int> ex = { 1, 2, 3 };
    auto s = vec | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = vec | limit(0) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    s = empty<int>() | limit(42) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    s = vec | limit(vec.size() + 1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), vec.begin(), vec.end());
}

BOOST_AUTO_TEST_SUITE_END()
