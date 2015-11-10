      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( product_init )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1 }) | product(1), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | product(1), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | product(1), 6);
    BOOST_CHECK_EQUAL(from({ -1, 2, 3 }) | product(1), -6);

    BOOST_CHECK_EQUAL(from({ 1 }) | product(2), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | product(2), 4);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | product(2), 12);
    BOOST_CHECK_EQUAL(from({ -1, 2, 3 }) | product(2), -12);

    BOOST_CHECK_EQUAL(empty<int>() | product(1), 1);
}

