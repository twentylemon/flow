      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( min_less )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | min().value(), 1);
    BOOST_CHECK_EQUAL(from({ 3, 2, 1 }) | min().value(), 1);
    BOOST_CHECK_EQUAL(from({ 3, 1, 2 }) | min().value(), 1);
    BOOST_CHECK_EQUAL(from({ 3, 3, 3 }) | min().value(), 3);
    BOOST_CHECK_EQUAL(from({ 2, 2, 3 }) | min().value(), 2);
    BOOST_CHECK_EQUAL(from({ 3 }) | min().value(), 3);

    auto i = empty<int>() | min();
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(-1), -1);
}

