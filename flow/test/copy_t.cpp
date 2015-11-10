      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( copy_t )  
{
    using namespace flow;

    std::vector<int> vec;
    std::vector<int> emp;
    std::vector<int> res = { 1, 2, 3 };

    res | copy(std::back_inserter(vec));
    BOOST_CHECK_EQUAL_COLLECTIONS(res.begin(), res.end(), vec.begin(), vec.end());

    vec.clear();
    empty<int>() | copy(std::back_inserter(vec));
    BOOST_CHECK_EQUAL_COLLECTIONS(emp.begin(), emp.end(), vec.begin(), vec.end());
}

