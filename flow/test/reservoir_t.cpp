      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( reservoir_t )  
{
    using namespace flow;

    std::vector<int> ex = { 1 };
    auto s = repeat(1, 1000) | reservoir(1);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 1, 1 };
    s = repeat(1, 1000) | reservoir(3);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = empty<int>() | reservoir(1);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 1, 1 };
    s = repeat(1) | reservoir(3);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = repeat(1) | reservoir(0);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

