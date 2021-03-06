      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( from_itr )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3, 4, 5, 6 };

    std::vector<int> ex = vec;
    auto s = from(vec.begin(), vec.end()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 2, 3 };
    s = from(vec.begin(), vec.begin() + 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = from(vec.end(), vec.end()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 3, 4, 5 };
    s = from(vec.begin() + 2, vec.begin() + 5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

