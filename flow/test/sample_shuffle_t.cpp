      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( sample_shuffle_t )  
{
    using namespace flow;

    std::vector<int> ex = { 1 };
    auto s = from({ 1 }) | sample_shuffle(1);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    s = from({ 1, 1, 1, 1, 1 }) | sample_shuffle(1);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    s = from({ 1 }) | sample_shuffle(5);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = empty<int>() | sample_shuffle(1);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

