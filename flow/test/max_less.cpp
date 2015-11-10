      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( max_less )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | max().value(), 3);
    BOOST_CHECK_EQUAL(from({ 3, 2, 1 }) | max().value(), 3);
    BOOST_CHECK_EQUAL(from({ 1, 3, 2 }) | max().value(), 3);
    BOOST_CHECK_EQUAL(from({ 3, 3, 3 }) | max().value(), 3);
    BOOST_CHECK_EQUAL(from({ 3, 2, 3 }) | max().value(), 3);
    BOOST_CHECK_EQUAL(from({ 3 }) | max().value(), 3);

    auto i = empty<int>() | max();
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(-1), -1);
}

