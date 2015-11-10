      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( map_func )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3, 4, 5, 6 };

    std::vector<int> ex = { 2, 4, 6, 8, 10, 12 };
    auto s = vec | map([](int i) { return 2 * i; }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<double> ex2 = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    auto s2 = vec | map([](int i) { return 0.0; }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());

    ex2 = {};
    s2 = empty<int>() | map([](int i) { return 0.0; }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());

    std::vector<Widget> w = { Widget(1), Widget(2), Widget(3) };
    std::vector<bool> ex3 = { true, false, true };
    auto s3 = w | map([](Widget& w) { return !w.is_even(); }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex3.begin(), ex3.end());
}

