      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( product_opt )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1 }) | product().value(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | product().value(), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | product().value(), 6);
    BOOST_CHECK_EQUAL(from({ -1, 2, 3 }) | product().value(), -6);

    auto i = empty<int>() | product();
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(1), 1);
}

