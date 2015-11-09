      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( peek_member_const )  
{
    using namespace flow;

    std::vector<Widget> vec = { Widget(1), Widget(2) };
    vec | peek(&Widget::process) | execute();
    for (Widget& w : vec) {
        BOOST_CHECK_EQUAL(w._other, w._value);
    }

    vec = { Widget(1), Widget(2) };
    vec | peek(&Widget::process);
    for (Widget& w : vec) {
        BOOST_CHECK_EQUAL(w._other, DEFAULT_OTHER);
    }
}

