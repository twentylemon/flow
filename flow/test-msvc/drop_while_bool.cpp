      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( drop_while_bool )  
{
    using namespace flow;

    std::vector<bool> vec1 = { false, false };
    auto vec2 = from({ true, true, false, false }) | drop_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<bool>() | drop_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ true, true }) | drop_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { false, false, false };
    vec2 = from({ false, false, false }) | drop_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { false, true };
    vec2 = from({ true, false, true }) | drop_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

