      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( rfrom_container )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3, 4 };

    std::vector<int> ex = { 4, 3, 2, 1 };
    auto s = rfrom(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    vec = {};
    ex = {};
    s = rfrom(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

