      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( replace_map_t )  
{
    using namespace flow;

    std::vector<int> ex = { 1, -2, 3 };
    auto s = from({ 1, 2, 3 }) | replace_map(is_even, negate) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | replace_map(is_even, negate) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 1 };
    s = from({ 1, 1, 1 }) | replace_map(is_even, negate) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { -2, -2, 2 };
    s = from({ 2, 2, -2 }) | replace_map(is_even, negate) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

