      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( slice_op )  
{
    using namespace flow;

    std::vector<int> ex = { 3, 4, 5 };
    auto s = from({ 1, 2, 3, 4, 5 }) | slice(2, 5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 2, 3, 4 };
    s = from({ 1, 2, 3, 4, 5 }) | slice(1, 4) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | slice(0, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    s = from({ 1, 2, 3 }) | slice(3, 4) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 2, 3, 4, 5 };
    s = from({ 1, 2, 3, 4, 5 }) | slice(0, 42) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = from({ 1, 2, 3, 4, 5 }) | slice(42, 43) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

