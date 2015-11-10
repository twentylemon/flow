      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( range_inc )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 3, 5 };
    auto s = range(1, 6, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1 };
    s = range(1, 2, 100) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 3 };
    s = range(1, 5, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = range(1, 1, 100) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

