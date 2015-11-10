      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( any_member_const )  
{
    using namespace flow;

    const std::vector<Widget> vec1 = { Widget(1), Widget(2) };
    const std::vector<Widget> vec2 = { Widget(1), Widget(1) };
    BOOST_CHECK_EQUAL(vec1 | any(&Widget::is_even), true);
    BOOST_CHECK_EQUAL(vec2 | any(&Widget::is_even), false);
}

