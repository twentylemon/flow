      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( any_member )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ Widget(1), Widget(2) }) | any(&Widget::is_even), true);
    BOOST_CHECK_EQUAL(from({ Widget(1), Widget(3) }) | any(&Widget::is_even), false);
}

