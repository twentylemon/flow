      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( min_comp )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ -4, 3, 2 }) | min(square_less).value(), 2);
    BOOST_CHECK_EQUAL(from({ 2, 3, -4 }) | min(square_less).value(), 2);
    BOOST_CHECK_EQUAL(from({ -4, 2, 3 }) | min(square_less).value(), 2);
    BOOST_CHECK_EQUAL(from({ 2, -4, 2, 3 }) | min(square_less).value(), 2);
    BOOST_CHECK_EQUAL(from({ 4, -4, -4 }) | min(square_less).value(), 4);
    BOOST_CHECK_EQUAL(from({ 3 }) | min(square_less).value(), 3);

    auto i = empty<int>() | min(square_less);
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(-1), -1);
}

