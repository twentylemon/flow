      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( sum_init )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1 }) | sum(0), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | sum(0), 3);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | sum(0), 6);
    BOOST_CHECK_EQUAL(from({ -1, 2, 3 }) | sum(0), 4);

    BOOST_CHECK_EQUAL(from({ 1 }) | sum(2), 3);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | sum(2), 5);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | sum(2), 8);
    BOOST_CHECK_EQUAL(from({ -1, 2, 3 }) | sum(2), 6);

    BOOST_CHECK_EQUAL(empty<int>() | sum(0), 0);
}

