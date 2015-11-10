      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( last_t )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1 }) | last().value(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | last().value(), 3);

    auto i = empty<int>() | last();
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(3), 3);
}

