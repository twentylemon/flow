      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( any_bool )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ true, false }) | any(), true);
    BOOST_CHECK_EQUAL(from({ false, false, false }) | any(), false);
    BOOST_CHECK_EQUAL(empty<bool>() | any(), false);
}

