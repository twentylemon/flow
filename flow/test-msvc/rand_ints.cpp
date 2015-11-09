      
#include "stdafx.h"

#define DO_CHECK(min, max) BOOST_CHECK(random_ints(min, max) | limit(1000) | all([=](auto i) { return i >= min && i <= max; }))

BOOST_AUTO_TEST_CASE( rand_ints )  
{
    using namespace flow;

    DO_CHECK(0, 5);
    DO_CHECK(-100, 100);
    DO_CHECK(1, 1);
    DO_CHECK(0, 1);
}

