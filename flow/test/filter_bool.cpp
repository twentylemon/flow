      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( filter_bool )  
{
    using namespace flow;

    std::vector<bool> vec1 = { true, true };
    auto vec2 = from({ true, true, false, false }) | filter() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<bool>() | filter() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { true, true };
    vec2 = from({ true, true }) | filter() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ false, false, false }) | filter() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { true, true };
    vec2 = from({ true, false, true }) | filter() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

