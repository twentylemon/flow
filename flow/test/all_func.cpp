      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( all_func )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | all(is_even), false);
    BOOST_CHECK_EQUAL(from({ 2, 4, 6 }) | all(is_even), true);
    BOOST_CHECK_EQUAL(empty<int>() | all(is_even), true);

    auto s = from({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL(s | all(is_even), false);
}

