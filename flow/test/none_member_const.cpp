      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( none_member_const )  
{
    using namespace flow;

    const std::vector<Widget> vec1 = { Widget(1), Widget(2) };
    const std::vector<Widget> vec2 = { Widget(1), Widget(3) };
    BOOST_CHECK_EQUAL(vec1 | none(&Widget::is_even), false);
    BOOST_CHECK_EQUAL(vec2 | none(&Widget::is_even), true);
}

