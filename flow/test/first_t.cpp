      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( first_t )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1 }) | first().value(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | first().value(), 1);

    auto i = empty<int>() | first();
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(4), 4);
}

