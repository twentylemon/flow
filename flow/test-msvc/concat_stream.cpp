      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( concat_stream )  
{
    using namespace flow;

    std::vector<int> vec1 = {};
    auto vec2 = empty<int>() | concat(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 1, 2, 3, 4 };
    vec2 = from({ 1, 2 }) | concat(from({ 3, 4 })) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 1, 2, 3, 4 };
    vec2 = from({ 1, 2 }) | concat(from({ 4, 3 }) | reverse()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 3, 4 };
    vec2 = empty<int>() | concat(from({ 4, 3 }) | reverse()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

