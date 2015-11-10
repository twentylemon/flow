      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( iterate_func )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 2, 3 };
    auto s = iterate([](int i) { return ++i; }, 1) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 0, 1, 1, 2, 3, 5, 8 };
    s = iterate(std::plus<int>(), 0, 1) | limit(7) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 2, 2, 4, 8, 32 };
    s = iterate(std::multiplies<int>(), 1, 2) | limit(6) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 0 };
    s = iterate([](int i, int j, int k) { return i + j + k; }, 0, 1, 2) | limit(1) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

