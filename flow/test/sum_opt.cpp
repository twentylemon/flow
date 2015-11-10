      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( sum_opt )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1 }) | sum().value(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | sum().value(), 3);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | sum().value(), 6);
    BOOST_CHECK_EQUAL(from({ -1, 2, 3 }) | sum().value(), 4);

    auto i = empty<int>() | sum();
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(1), 1);
}

