
#include "test.h"

BOOST_AUTO_TEST_CASE(iterator_t) {
    std::vector<int> vec;
    std::vector<int> ex = { 1, 2, 3, 4 };
    auto s = from({ 1, 2, 3, 4 });
    std::copy(s.begin(), s.end(), std::back_inserter(vec));
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), vec.begin(), vec.end());

    auto s2 = iota(1) | filter(is_even) | limit(10);
    ex = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex.begin(), ex.end());

    auto s3 = empty<int>();
    ex = {};
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex.begin(), ex.end());
}
