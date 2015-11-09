      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( cycle_itr_n )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 1, 2, 3, 1, 2, 3 };
    auto s = cycle(vec.begin(), vec.end(), 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 1 };
    s = cycle(vec.begin(), vec.begin() + 1, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

