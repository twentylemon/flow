      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( sort_comp )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 2, 3 };
    auto s = from({ 2, 3, 1 }) | sort(square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | sort(square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

