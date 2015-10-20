
#include "../test.h"

BOOST_AUTO_TEST_CASE(shuffle_t) {
    std::vector<int> v = { 1 };

    auto s = v | shuffle(std::mt19937()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), v.begin(), v.end());

    v = {};
    s = empty<int>() | shuffle() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), v.begin(), v.end());

    s = cycle({ 1, 2, 3 }, 5) | shuffle() | to_vector();
    BOOST_CHECK_EQUAL(s | count(1), 5);
    BOOST_CHECK_EQUAL(s | count(2), 5);
    BOOST_CHECK_EQUAL(s | count(3), 5);
    BOOST_CHECK_EQUAL(s.size(), 15);
}
