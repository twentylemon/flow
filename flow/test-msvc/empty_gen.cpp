      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( empty_gen )  
{
    using namespace flow;

    std::vector<int> ex = {};
    auto s = empty<int>() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    BOOST_CHECK_EQUAL(empty<int>() | count(), 0);
}

