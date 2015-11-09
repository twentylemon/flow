      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( concat_itr )  
{
    using namespace flow;
    
    std::vector<int> vec1 = {};
    std::vector<int> vec3 = {};
    auto vec2 = empty<int>() | concat(vec3.begin(), vec3.end()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec3 = { 3, 4 };
    vec1 = { 1, 2, 3, 4 };
    vec2 = from({ 1, 2 }) | concat(vec3.begin(), vec3.end()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec3 = { 1, 2, 3 };
    vec1 = { 1, 2, 1, 2 };
    vec2 = from({ 1, 2 }) | concat(vec3.begin(), vec3.begin() + 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

