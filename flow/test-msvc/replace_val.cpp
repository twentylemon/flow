      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( replace_val )  
{
    using namespace flow;

    std::vector<int> ex = { 3, 2, 3 };
    auto s = from({ 1, 2, 3 }) | replace(1, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 2, 3 };
    s = from({ 1, 2, 3 }) | replace(0, 5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | replace(0, 1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 2, 2, 2 };
    s = from({ 1, 1, 1 }) | replace(1, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

