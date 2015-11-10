      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( none_bool )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ true, false }) | none(), false);
    BOOST_CHECK_EQUAL(from({ false, false, false }) | none(), true);
    BOOST_CHECK_EQUAL(empty<bool>() | none(), true);
}

