      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( slice_step )  
{
    using namespace flow;

    std::vector<int> ex = { 3, 4, 5 };
    auto s = from({ 1, 2, 3, 4, 5 }) | slice(2, 5, 1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 2, 4 };
    s = from({ 1, 2, 3, 4, 5 }) | slice(1, 4, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | slice(10, 20, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    s = from({ 1, 2, 3 }) | slice(4, 5, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 3 };
    s = from({ 1, 2, 3, 4, 5 }) | slice(0, 3, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

