      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( max_comp )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ -4, 3, 2 }) | max(square_less).value(), -4);
    BOOST_CHECK_EQUAL(from({ 2, 3, -4 }) | max(square_less).value(), -4);
    BOOST_CHECK_EQUAL(from({ 2, -4, 3 }) | max(square_less).value(), -4);
    BOOST_CHECK_EQUAL(from({ 2, -4, -4, 3 }) | max(square_less).value(), -4);
    BOOST_CHECK_EQUAL(from({ -4, 4, 4 }) | max(square_less).value(), -4);
    BOOST_CHECK_EQUAL(from({ 3 }) | max(square_less).value(), 3);

    auto i = empty<int>() | max(square_less);
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(-1), -1);
}

