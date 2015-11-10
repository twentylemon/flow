      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( nth_t )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1 }) | nth(0).value(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | nth(0).value(), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | nth(1).value(), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | nth(2).value(), 3);

    auto i = empty<int>() | nth(0);
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(10), 10);

    auto j = from({ 1, 2, 3 }) | nth(4);
    BOOST_CHECK(!j);
    BOOST_CHECK_EQUAL(j.value_or(10), 10);
}

