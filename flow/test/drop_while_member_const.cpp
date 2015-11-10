      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( drop_while_member_const )  
{
    using namespace flow;

    std::vector<Widget> vec1 = { Widget(1), Widget(3) };
    auto vec2 = from({ Widget(2), Widget(1), Widget(3) }) | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    const auto vec3 = vec1;
    vec2 = vec3 | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ Widget(2), Widget(2) }) | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { Widget(1), Widget(2) };
    vec2 = from({ Widget(1), Widget(2) }) | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

