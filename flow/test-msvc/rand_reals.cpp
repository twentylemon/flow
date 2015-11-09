      
#include "stdafx.h"

#define DO_CHECK(min, max) BOOST_CHECK(random_reals(min, max) | limit(1000) | all([=](auto i) { return i >= min && i <= max; }))

BOOST_AUTO_TEST_CASE( rand_reals )  
{
    using namespace flow;

    DO_CHECK(0.0, 1.0);
    DO_CHECK(-100.0, 100.0);
    DO_CHECK(-1000000.0, -5000.0);
}

