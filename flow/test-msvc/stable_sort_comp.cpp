      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( stable_sort_comp )  
{
    using namespace flow;

    std::vector<Widget> ex = { Widget(1), Widget(2), Widget(3) };
    auto s = from({ Widget(2), Widget(3), Widget(1) }) | stable_sort(square_less_widget) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<Widget>() | stable_sort(square_less_widget) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { Widget(1, 0), Widget(-1, 1), Widget(-2, 0), Widget(2, 1) };
    s = from({ Widget(-2, 0), Widget(1, 0), Widget(-1, 1), Widget(2, 1) }) | stable_sort(square_less_widget) | to_vector();
    BOOST_CHECK_EQUAL(ex.size(), s.size());
    for (std::size_t i = 0; i < s.size(); ++i) {
        BOOST_CHECK_EQUAL(s[i], ex[i]);
        BOOST_CHECK_EQUAL(s[i]._other, ex[i]._other);
    }
}

