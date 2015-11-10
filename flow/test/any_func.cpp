      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( any_func )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | any(is_even), true);
    BOOST_CHECK_EQUAL(from({ 1, 3, 5 }) | any(is_even), false);
    BOOST_CHECK_EQUAL(empty<int>() | any(is_even), false);

    auto s = from({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL(s | any(is_even), true);
}

