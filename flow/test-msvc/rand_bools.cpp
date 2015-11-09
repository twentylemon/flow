      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( rand_bools )  
{
    using namespace flow;

    BOOST_CHECK(random_bools() | limit(1000) | all([](auto b) { return b || !b; }));
    BOOST_CHECK(random_bools() | limit(1000) | filter() | all());
}

