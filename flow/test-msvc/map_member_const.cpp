      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( map_member_const )  
{
    using namespace flow;

    std::vector<bool> ex = { false, true };
    auto s = from({ Widget(1), Widget(2) }) | map(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

