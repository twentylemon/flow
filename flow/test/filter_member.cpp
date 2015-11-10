      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( filter_member )  
{
    using namespace flow;

    std::vector<Widget> f1 = { Widget(2), Widget(1), Widget(3) };
    std::vector<Widget> vec1 = { Widget(2) };
    auto vec2 = f1 | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<Widget>() | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    f1 = { Widget(2), Widget(2) };
    vec1 = { Widget(2), Widget(2) };
    vec2 = f1 | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    f1 = { Widget(1), Widget(1) };
    vec1 = {};
    vec2 = f1 | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

