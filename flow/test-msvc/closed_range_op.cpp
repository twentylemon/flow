      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( closed_range_op )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 2, 3, 4, 5, 6 };
    auto s = closed_range(1, 6) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1 };
    s = closed_range(1, 1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

