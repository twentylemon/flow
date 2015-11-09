      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( cycle_container )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 1, 2, 3, 1, 2 };
    auto s = cycle(vec) | limit(5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    vec = { 1 };
    ex = { 1, 1, 1 };
    s = cycle(vec) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> w = { Widget(1), Widget(2) };
    std::vector<Widget> wex = { Widget(1), Widget(2), Widget(1) };
    auto sw = cycle(w) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
}

