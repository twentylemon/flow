      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( repeat_n )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 1, 1 };
    auto s = repeat(1, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 4, 4, 4, 4 };
    s = repeat(4, 4) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    BOOST_CHECK(repeat(1, 2) | contains(1));
    BOOST_CHECK_EQUAL(repeat(1, 2) | contains(2), false);
}

