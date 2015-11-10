      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( count_val )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(1), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(2), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(3), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count(0), 0);
    BOOST_CHECK_EQUAL(from({ 1 }) | count(1), 1);
    BOOST_CHECK_EQUAL(from({ 1 }) | count(0), 0);
    BOOST_CHECK_EQUAL(empty<int>() | count(0), 0);

    auto s = from({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL(s | count(1), 1);
    BOOST_CHECK_EQUAL(s | count(2), 1);
    BOOST_CHECK_EQUAL(s | count(3), 1);
    BOOST_CHECK_EQUAL(s | count(4), 0);
}

