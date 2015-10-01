
#include "../test.h"

BOOST_AUTO_TEST_CASE(first_t) {
    BOOST_CHECK_EQUAL(from({ 1 }) | first(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | first(), 1);

    BOOST_CHECK_THROW(empty<int>() | first(), std::out_of_range);
}
