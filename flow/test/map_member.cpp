      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( map_member )  
{
    using namespace flow;

    std::vector<Widget> vec = { Widget(1), Widget(2) };

    std::vector<bool> ex = { false, true };
    auto s = vec | map(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    // test that map keeps references
    vec | map(&Widget::get_other_ref) | each([](int& other) { other = DEFAULT_OTHER + 1; });
    for (Widget& w : vec) {
        BOOST_CHECK_EQUAL(w._other, DEFAULT_OTHER + 1);
    }
}

