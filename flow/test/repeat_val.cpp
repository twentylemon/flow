      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( repeat_val )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 1, 1 };
    auto s = repeat(1) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 4, 4, 4, 4 };
    s = repeat(4) | limit(4) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    BOOST_CHECK(repeat(1) | contains(1));
}

