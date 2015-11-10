      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( fold_opt )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold(std::plus<int>()).value(), 6);
    BOOST_CHECK_EQUAL(from({ 1, -2, 3 }) | fold(std::plus<int>()).value(), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | fold(std::minus<int>()).value(), -1);    // 1 - (2); 1 is the init
    BOOST_CHECK_EQUAL(from({ 1 }) | fold(std::plus<int>()).value(), 1);

    auto i = empty<int>() | fold(std::plus<int>());
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(4), 4);
}

