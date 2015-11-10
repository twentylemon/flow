      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( minmax_less )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | minmax().value(), std::make_pair(1, 3));
    BOOST_CHECK_EQUAL(from({ 3, 2, 1 }) | minmax().value(), std::make_pair(1, 3));
    BOOST_CHECK_EQUAL(from({ 3, 1, 2 }) | minmax().value(), std::make_pair(1, 3));
    BOOST_CHECK_EQUAL(from({ 3, 3, 3 }) | minmax().value(), std::make_pair(3, 3));
    BOOST_CHECK_EQUAL(from({ 2, 2, 3 }) | minmax().value(), std::make_pair(2, 3));
    BOOST_CHECK_EQUAL(from({ 3 }) | minmax().value(), std::make_pair(3, 3));

    auto i = empty<int>() | minmax();
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(std::make_pair(-1, -1)), std::make_pair(-1, -1));
}

