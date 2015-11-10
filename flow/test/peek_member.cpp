      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( peek_member )  
{
    using namespace flow;

    std::vector<Widget> vec = { Widget(1), Widget(2) };
    std::vector<Widget> ex = { Widget(0), Widget(0) };
    vec | peek(&Widget::clear) | execute();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), vec.begin(), vec.end());

    vec = { Widget(1), Widget(2) };
    ex = { Widget(1), Widget(2) };
    vec | peek(&Widget::clear);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), vec.begin(), vec.end());
}

