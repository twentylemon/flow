      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( skip_op )  
{
    using namespace flow;

    std::vector<int> ex = { 3, 4, 5 };
    auto s = from({ 1, 2, 3, 4, 5 }) | skip(2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 2, 3, 4, 5 };
    s = from({ 1, 2, 3, 4, 5 }) | skip(1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | skip(10) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    s = from({ 1, 2, 3 }) | skip(42) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 2, 3, 4, 5 };
    s = from({ 1, 2, 3, 4, 5 }) | skip(0) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

