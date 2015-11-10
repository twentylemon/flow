      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( take_while_func )  
{
    using namespace flow;

    std::vector<int> vec1 = { 1, 2 };
    auto vec2 = from({ 1, 2, 3, 4, 5, 6 }) | take_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<int>() | take_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 1, 2, 1, 2, 1 };
    vec2 = from({ 1, 2, 1, 2, 1 }) | take_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ 4, 5, 4, 5, 4 }) | take_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 2 };
    vec2 = from({ 2, 3, 2, 2 }) | take_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

