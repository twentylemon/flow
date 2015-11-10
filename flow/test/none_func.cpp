      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( none_func )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | none(is_even), false);
    BOOST_CHECK_EQUAL(from({ 1, 3, 1 }) | none(is_even), true);
    BOOST_CHECK_EQUAL(empty<int>() | none(is_even), true);
}

