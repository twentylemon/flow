      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( each_member_const )  
{
    using namespace flow;

    const std::vector<Widget> vec = { Widget(1), Widget(2) };
    vec | each(&Widget::process);
    for (const Widget& w : vec) {
        BOOST_CHECK_EQUAL(w._other, w._value);
    }
}

