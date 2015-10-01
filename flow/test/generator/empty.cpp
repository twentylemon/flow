
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_generator)

BOOST_AUTO_TEST_CASE(empty_t) {
    std::vector<int> ex = {};
    auto s = empty<int>() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    BOOST_CHECK_EQUAL(empty<int>() | count(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
