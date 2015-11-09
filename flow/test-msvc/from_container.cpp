      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( from_container )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3, 4 };

    std::vector<int> ex = vec;
    auto s = from(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    vec = {};
    ex = {};
    s = from(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

