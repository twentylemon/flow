      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( each_func )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3 };
    std::vector<int> v;
    from({ 1, 2, 3 }) | each([&v](int i) { v.push_back(i); });
    BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), vec.begin(), vec.end());

    std::vector<Widget> ex = { Widget(1), Widget(2) };
    std::vector<Widget> init = { Widget(0), Widget(0) };
    int i = 0;
    init | each([&i](Widget& w) { w._value = ++i; });
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), init.begin(), init.end());
}

