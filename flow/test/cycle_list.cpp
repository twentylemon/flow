      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( cycle_list )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 2, 3, 1, 2 };
    auto s = cycle({ 1, 2, 3 }) | limit(5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 1 };
    s = cycle({ 1 }) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> wex = { Widget(1), Widget(1), Widget(1), Widget(1) };
    auto sw = cycle({ Widget(1) }) | limit(4) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
}

