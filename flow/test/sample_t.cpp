      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( sample_t )  
{
    using namespace flow;

    std::vector<int> ex = { 1 };
    auto s = from({ 1 }) | sample(1);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    s = from({ 1, 1, 1, 1, 1 }) | sample(1);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    s = from({ 1 }) | sample(5);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = empty<int>() | sample(1);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

