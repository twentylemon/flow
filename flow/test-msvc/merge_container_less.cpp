      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( merge_container_less )  
{
    using namespace flow;

    std::vector<int> vec = {};

    std::vector<int> ex = {};
    auto s = empty<int>() | merge(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 2, 4, 6, 8 };
    ex = { 1, 2, 3, 4, 5, 6, 7, 8 };
    s = from({ 1, 3, 5, 7 }) | merge(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

