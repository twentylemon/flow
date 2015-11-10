      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( all_member )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ Widget(1), Widget(2) }) | all(&Widget::is_even), false);
    BOOST_CHECK_EQUAL(from({ Widget(2), Widget(4) }) | all(&Widget::is_even), true);
}

