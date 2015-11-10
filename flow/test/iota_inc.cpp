      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( iota_inc )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 3, 5 };
    auto s = iota(1, 2) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { -1, 1, 3 };
    s = iota(-1, 2) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 8, 7, 6, 5, 4, 3 };
    s = iota(8, -1) | limit(6) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

