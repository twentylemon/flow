      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( range_op )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 2, 3, 4, 5 };
    auto s = range(1, 6) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1 };
    s = range(1, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = range(1, 1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

