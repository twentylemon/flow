      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( each_member )  
{
    using namespace flow;

    std::vector<Widget> zero = { Widget(0), Widget(0) };
    std::vector<Widget> vec = { Widget(1), Widget(2) };
    vec | each(&Widget::clear);
    BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(), zero.begin(), zero.end());
}

