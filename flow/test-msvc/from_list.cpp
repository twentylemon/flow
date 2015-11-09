      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( from_list )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 2, 3 };
    auto s = from({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = from<int>({}) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

