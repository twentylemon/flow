      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( count_t )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(), 3);
    BOOST_CHECK_EQUAL(empty<int>() | count(), 0);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | filter(is_even) | count(), 1);

    auto s = from({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL(s | count(), s.size());
}

