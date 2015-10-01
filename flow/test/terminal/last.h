
#include "../test.h"

BOOST_AUTO_TEST_CASE(last_t) {
    BOOST_CHECK_EQUAL(from({ 1 }) | last(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | last(), 3);

    BOOST_CHECK_THROW(empty<int>() | last(), std::out_of_range);
}
