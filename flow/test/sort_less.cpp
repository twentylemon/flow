      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( sort_less )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 2, 3 };
    auto s = from({ 2, 3, 1 }) | sort() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | sort() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 2, 2, 3, 3 };
    s = from({ 2, 1, 2, 1, 3, 3 }) | sort() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

