      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( none_member )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ Widget(1), Widget(2) }) | none(&Widget::is_even), false);
    BOOST_CHECK_EQUAL(from({ Widget(1), Widget(3) }) | none(&Widget::is_even), true);
}

