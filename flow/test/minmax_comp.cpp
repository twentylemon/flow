      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( minmax_comp )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ -4, 3, 2 }) | minmax(square_less).value(), std::make_pair(2, -4));
    BOOST_CHECK_EQUAL(from({ 2, 3, -4 }) | minmax(square_less).value(), std::make_pair(2, -4));
    BOOST_CHECK_EQUAL(from({ -4, 2, 3 }) | minmax(square_less).value(), std::make_pair(2, -4));
    BOOST_CHECK_EQUAL(from({ 2, -4, 4, -2, 3 }) | minmax(square_less).value(), std::make_pair(2, 4));
    BOOST_CHECK_EQUAL(from({ 4, -4, -4 }) | minmax(square_less).value(), std::make_pair(4, 4));
    BOOST_CHECK_EQUAL(from({ 2, 4, -4, -4 }) | minmax(square_less).value(), std::make_pair(2, -4));
    BOOST_CHECK_EQUAL(from({ 3 }) | minmax(square_less).value(), std::make_pair(3, 3));

    auto i = empty<int>() | minmax(square_less);
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(std::make_pair(-1, -1)), std::make_pair(-1, -1));
}

