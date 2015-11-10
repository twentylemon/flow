      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( all_bool )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ true, false }) | all(), false);
    BOOST_CHECK_EQUAL(from({ true, true, true }) | all(), true);
    BOOST_CHECK_EQUAL(from({ true, false, true }) | all(), false);
    BOOST_CHECK_EQUAL(from({ false, false }) | all(), false);
    BOOST_CHECK_EQUAL(empty<bool>() | all(), true);
}

