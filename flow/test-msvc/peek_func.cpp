      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( peek_func )  
{
    using namespace flow;

    std::vector<int> vec;
    std::vector<int> ex = { 1, 2, 3 };
    ex | peek([&vec](int i) { vec.push_back(i); }) | execute();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), vec.begin(), vec.end());

    vec = {};
    std::vector<int> ex2 = {};
    ex | peek([&vec](int i) { vec.push_back(i); }); // lazy; no items should be pushed
    BOOST_CHECK_EQUAL_COLLECTIONS(ex2.begin(), ex2.end(), vec.begin(), vec.end());
}

