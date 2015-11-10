      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( rcycle_container_n )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 3, 2, 1, 3, 2, 1 };
    auto s = rcycle(vec, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    vec = { 1 };
    ex = { 1, 1, 1 };
    s = rcycle(vec, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> w = { Widget(1), Widget(2) };
    std::vector<Widget> wex = { Widget(2), Widget(1), Widget(2), Widget(1) };
    auto sw = rcycle(w, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
}

