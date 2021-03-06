      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( dump_t )  
{
    using namespace flow;

    std::stringstream str;
    from({ 1, 2, 3 }) | dump(str);
    BOOST_CHECK_EQUAL(str.str(), "1 2 3 ");

    str.str("");
    empty<int>() | dump(str);
    BOOST_CHECK_EQUAL(str.str(), "");

    str.str("");
    from({ 1, 2, 3 }) | dump(str, "hi");
    BOOST_CHECK_EQUAL(str.str(), "1hi2hi3hi");
}

