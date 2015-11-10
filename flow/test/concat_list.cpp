      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( concat_list )  
{
    using namespace flow;

    std::vector<int> vec1 = { 1, 2, 3 };
    auto vec2 = empty<const int>() | concat({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 1, 2, 3, 4 };
    vec2 = from({ 1, 2 }) | concat({ 3, 4 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 1, 2, 1, 2, 3 };
    vec2 = from({ 1, 2 }) | concat({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

