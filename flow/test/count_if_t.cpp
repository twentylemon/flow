      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( count_if_t )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count_if([](int i) { return i < 4; }), 3);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count_if([](int i) { return i < 3; }), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count_if([](int i) { return i < 2; }), 1);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | count_if([](int i) { return i < 1; }), 0);
    BOOST_CHECK_EQUAL(from({ 1 }) | count_if([](int i) { return i > 0; }), 1);
    BOOST_CHECK_EQUAL(from({ 0 }) | count_if([](int i) { return i > 0; }), 0);
    BOOST_CHECK_EQUAL(empty<int>() | count_if([](int i) { return true; }), 0);

    auto s = from({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL(s | count_if(is_even), 1);
    BOOST_CHECK_EQUAL(s | count_if([](int i) { return false; }), 0);
}

