      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( replace_if_t )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 3, 3 };
    auto s = from({ 1, 2, 3 }) | replace_if(is_even, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | replace_if(is_even, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 1 };
    s = from({ 1, 1, 1 }) | replace_if(is_even, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 3, 3, 3 };
    s = from({ 2, 2, 2 }) | replace_if(is_even, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

