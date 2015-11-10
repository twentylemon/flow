      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( filter_func )  
{
    using namespace flow;

    std::vector<int> vec1 = { 2, 4, 6 };
    auto vec2 = from({ 1, 2, 3, 4, 5, 6 }) | filter(is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<int>() | filter(is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ 1, 3, 1, 5 }) | filter(is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 2, 2, 2 };
    vec2 = from({ 2, 2, 2 }) | filter(is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    std::vector<Widget> w = { Widget(1), Widget(2), Widget(3) };
    std::vector<Widget> ex = { Widget(1), Widget(3) };
    auto s = w | filter([](Widget& w) { return !w.is_even(); }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

