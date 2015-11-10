      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( fold_init )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold(std::plus<int>(), 0), 6);
    BOOST_CHECK_EQUAL(from({ 1, -2, 3 }) | fold(std::plus<int>(), 0), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | fold(std::minus<int>(), 0), -3);
    BOOST_CHECK_EQUAL(from({ 1 }) | fold(std::plus<int>(), 0), 1);

    BOOST_CHECK_EQUAL(empty<int>() | fold(std::plus<int>(), 0), 0);
}

