      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( cycle_container_n )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 1, 2, 3, 1, 2, 3 };
    auto s = cycle(vec, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    vec = { 1 };
    ex = { 1, 1, 1 };
    s = cycle(vec, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> w = { Widget(1), Widget(2) };
    std::vector<Widget> wex = { Widget(1), Widget(2), Widget(1), Widget(2) };
    auto sw = cycle(w, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
}

