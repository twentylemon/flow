      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( skip_every_t )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 3, 5 };
    auto s = from({ 1, 2, 3, 4, 5 }) | skip_every(2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 3 };
    s = from({ 1, 2, 3, 4 }) | skip_every(2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | skip_every(1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 2, 3, 4, 5 };
    s = from({ 1, 2, 3, 4, 5 }) | skip_every(1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

